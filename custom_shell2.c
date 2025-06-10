#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_TOKENS 64
#define MAX_COMMANDS 10
#define DELIM " \t\r\n"

#define HISTORY_FILE ".myshell_history"
#define MAX_HISTORY_SIZE 1000

void execute_command(char **args, int input_fd, int output_fd, int background);
void execute_pipeline(char ***commands, int cmd_count, int background);
void handle_redirection(char **args);

int is_builtin(char **args);
int do_builtin(char **args);

void parse_and_execute(char *line);

int main() {
    char hist_path[512];
    snprintf(hist_path, sizeof(hist_path), "%s/%s", getenv("HOME"), HISTORY_FILE);
    
    // Load history file and limit size
    read_history(hist_path);
    stifle_history(MAX_HISTORY_SIZE);

    // Load startup file ~/.myshellrc
    char rc_path[256];
    snprintf(rc_path, sizeof(rc_path), "%s/.myshellrc", getenv("HOME"));
    FILE *rc = fopen(rc_path, "r");
    if (rc) {
        char *line = NULL;
        size_t len = 0;
        while (getline(&line, &len, rc) != -1) {
            parse_and_execute(line);
        }
        free(line);
        fclose(rc);
    }

    char *input;
    while ((input = readline("myshell> ")) != NULL) {
        if (strlen(input) != 0) {
            HIST_ENTRY *last = previous_history();
            if (!last || strcmp(last->line, input) != 0) {
                add_history(input);
            }
            parse_and_execute(input);
        }
        free(input);
    }

    // Save history on exit
    write_history(hist_path);

    printf("\n");
    return 0;
}

void parse_and_execute(char *line) {
    int background = 0;
    // Check for background execution
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '&') {
        background = 1;
        line[len - 1] = '\0'; // Remove '&' from line
    }

    // Split line by pipes '|'
    char *pipe_segments[MAX_COMMANDS];
    int cmd_count = 0;

    char *saveptr1;
    char *segment = strtok_r(line, "|", &saveptr1);
    while (segment != NULL && cmd_count < MAX_COMMANDS) {
        while (*segment == ' ') segment++; // Trim leading spaces
        pipe_segments[cmd_count++] = segment;
        segment = strtok_r(NULL, "|", &saveptr1);
    }

    // Parse each segment into args
    char **commands[MAX_COMMANDS];
    for (int i = 0; i < cmd_count; i++) {
        commands[i] = malloc(sizeof(char *) * (MAX_TOKENS));
        int arg_count = 0;

        // Tokenize the segment
        char *saveptr2;
        char *token = strtok_r(pipe_segments[i], DELIM, &saveptr2);
        while (token != NULL && arg_count < MAX_TOKENS - 1) {
            commands[i][arg_count++] = token;
            token = strtok_r(NULL, DELIM, &saveptr2);
        }
        commands[i][arg_count] = NULL;
    }

    if (cmd_count == 1 && is_builtin(commands[0])) {
        do_builtin(commands[0]);
        free(commands[0]);
    } else {
        execute_pipeline((char ***)commands, cmd_count, background);
        for (int i = 0; i < cmd_count; i++) {
            free(commands[i]);
        }
    }
}

int is_builtin(char **args) {
    if (args[0] == NULL) return 0;
    return (strcmp(args[0], "cd") == 0 || strcmp(args[0], "exit") == 0);
}

int do_builtin(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "myshell: expected argument to \"cd\"\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("myshell");
            }
        }
        return 1;
    } else if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }
    return 0;
}

void handle_redirection(char **args) {
    int i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], ">") == 0) {
            args[i] = NULL; // terminate args before >
            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            break;
        } else if (strcmp(args[i], "<") == 0) {
            args[i] = NULL; // terminate args before <
            int fd = open(args[i+1], O_RDONLY);
            if (fd < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            break;
        }
        i++;
    }
}

void execute_pipeline(char ***commands, int cmd_count, int background) {
    int i;
    int in_fd = 0;  // Start with stdin
    int pipefd[2];

    pid_t pids[MAX_COMMANDS];

    for (i = 0; i < cmd_count; i++) {
        if (i < cmd_count - 1) {
            if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid_t pid = fork();
        if (pid == 0) {
            // Child process

            if (in_fd != 0) {
                dup2(in_fd, 0);
                close(in_fd);
            }
            if (i < cmd_count - 1) {
                close(pipefd[0]);
                dup2(pipefd[1], 1);
                close(pipefd[1]);
            }

            // Handle input/output redirection
            handle_redirection(commands[i]);

            execvp(commands[i][0], commands[i]);
            perror("myshell");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            pids[i] = pid;
            if (in_fd != 0) close(in_fd);
            if (i < cmd_count - 1) {
                close(pipefd[1]);
                in_fd = pipefd[0];
            }
        }
    }

    // Parent waits if not background
    if (!background) {
        for (i = 0; i < cmd_count; i++) {
            waitpid(pids[i], NULL, 0);
        }
    } else {
        printf("[Running in background]\n");
    }
}
