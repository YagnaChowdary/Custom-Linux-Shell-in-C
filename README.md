# Custom Linux Shell in C

A fully functional custom shell implemented in C that mimics basic functionalities of modern Unix shells like `bash` or `zsh`.

---

## 🚀 Features

* 🧾 **Command history** using GNU Readline
* 🔁 **Piping** with `|`
* 📤 **I/O Redirection**: `>`, `>>`, `<`
* 🧠 **Environment variable expansion** (e.g., `$HOME`, `$USER`)
* 🪄 **Built-in commands**: `cd`, `exit`
* ⚙️ **Background process support** using `&`
* 📂 **RC file loader**: executes commands from `~/.myshellrc` on startup

---

## 🛠️ Installation

1. Clone the repo:

   ```bash
   git clone https://github.com/yagna_Chowdary/custom-linux-shell.git
   cd custom-linux-shell
   ```

2. Compile the code:

   ```bash
   gcc -o myshell custom_shell.c -lreadline
   ```

3. Run the shell:

   ```bash
   ./myshell
   ```

---

## ✨ Usage

```bash
myshell> echo Hello World
myshell> cat file.txt | grep error | sort > result.txt
myshell> cd /home/user/Documents
myshell> sleep 10 &
```

---

## 🔧 .myshellrc Example

Create a file in your home directory `~/.myshellrc`:

```bash
# This file is loaded at shell startup
cd ~
echo Welcome to MyShell!
export PATH=$PATH:~/myshell-bin
```

---

---

## 🔧 Features Implemented

| Feature                       | Description                                                                                                                                                                                                                                                            |                                                                                                                                                                                                                |
| ----------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Command Execution**         | Allows execution of system commands like `ls`, `pwd`, `whoami`, and `date`. The shell parses user input and uses `fork()` and `execvp()` to run these commands. Useful to interact directly with the OS, and shows understanding of process creation and system calls. |                                                                                                                                                                                                                |
| **Redirection**               | Supports output redirection using `>` (overwrite) and `>>` (append) to write command outputs to files. Implemented using file descriptor manipulation and `dup2()`. This is commonly used in scripting and logging outputs.                                            |                                                                                                                                                                                                                |
| **Piping**                    | Enables piping using \`                                                                                                                                                                                                                                                | `so the output of one command becomes input to another. Achieved using`pipe()`, `fork()`, and `dup2()\` calls to manage inter-process communication. Helps in chaining Unix utilities for powerful one-liners. |
| **Background Execution**      | Allows commands to run in the background with `&`, so users can continue using the shell while jobs execute asynchronously. Handled via process tracking and `waitpid()` with `WNOHANG`. Enables multitasking inside the shell.                                        |                                                                                                                                                                                                                |
| **Built-in Commands**         | Includes shell-internal commands like `cd`, `exit`, and `history` that are handled without creating new processes. For example, `cd` uses `chdir()` directly within the shell process. Essential for maintaining shell state.                                          |                                                                                                                                                                                                                |
| **Job Control**               | Users can run jobs in the background and control them using `jobs`, `fg`, and `bg` commands. Maintains job list and process status using signal handling and process IDs. Demonstrates understanding of process states and signal delivery.                            |                                                                                                                                                                                                                |
| **Multiple Commands**         | Allows chaining of multiple commands on a single line separated by `;`. The shell parses input to execute commands sequentially. Useful in scripting or executing batch commands.                                                                                      |                                                                                                                                                                                                                |
| **Signal Handling**           | Custom handlers for `SIGINT` (Ctrl+C) and `SIGTSTP` (Ctrl+Z) ensure smooth interruption and suspension of foreground processes without crashing the shell. Involves registering custom handlers using `signal()` or `sigaction()`.                                     |                                                                                                                                                                                                                |
| **Invalid Command Detection** | Displays friendly error messages for unrecognized or mistyped commands instead of crashing. This is done by checking `execvp()` return values. Improves shell usability and robustness.                                                                                |                                                                                                                                                                                                                |

---

## 📄 Sample Script Output

```shell
myshell> ./test_script.sh
=== BASIC COMMANDS ===
/home/yagna/custom-linux-shell
yagna
Tue Jun 17 13:09:09 IST 2025
=== REDIRECTION ===
Hello from test script
Hello from test script
Another line
=== PIPING ===
-rw-r--r-- 1 yagna yagna  4571 Jun  6 19:50 custom_shell.c
-rw-r--r-- 1 yagna yagna  5972 Jun 17 12:52 custom_shell2.c
-rw-r--r-- 1 yagna yagna    93 Jun  6 19:53 myshellrc.sample
-rwxr-xr-x 1 yagna yagna   595 Jun 17 13:07 test_script.sh
=== BACKGROUND JOB ===
=== BUILT-IN COMMANDS ===
/home/yagna
=== INVALID COMMAND ===
./test_script.sh: line 25: invalidcommand: command not found
=== JOB CONTROL ===
[1]-  Running                 sleep 5 &  (wd: ~/custom-linux-shell)
[2]+  Running                 sleep 15 &
=== HISTORY ===
=== MULTIPLE COMMANDS ===
a.txt  b.txt
=== SIGNAL TEST ===
=== END OF SCRIPT ===
myshell>
```

---
---

## 🛠 Build & Run

```bash
gcc -o myshell custom_shell.c
./myshell
```

For testing with script:

```bash
chmod +x test_script.sh
./test_script.sh
```

---
## 📚 Dependencies

* GCC
* GNU Readline (`libreadline-dev` on Linux)

Install Readline if not present:

```bash
sudo apt install libreadline-dev
```

--
## Key Features

**Interactive Command Line Interface**

- Uses GNU readline library for command input with line editing capabilities
- Maintains command history that persists across sessions
- Supports a startup configuration file (`~/.myshellrc`)


**Core Shell Functionality**

- **Built-in commands**: `cd` for directory navigation and `exit` to quit
- **External command execution**: Runs system programs and utilities
- **Pipeline support**: Connect commands with pipes (`|`) for data flow between processes
- **Background execution**: Run commands in background using `&` suffix
- **I/O redirection**: Redirect input (`<`) and output (`>`) to/from files


**Advanced Process Management**

- Creates child processes using `fork()` and `execvp()`
- Handles multiple processes in pipelines
- Proper cleanup and waiting for child processes
- Background process notification


## Code Structure

```c project="Custom Shell" file="myshell.c"
...
```

## Usage Examples

Once compiled, you can use the shell like this:

```shellscript
# Basic commands
myshell> ls -la
myshell> cd /home/user

# Pipelines
myshell> ls | grep .txt | wc -l

# I/O redirection
myshell> echo "Hello World" > output.txt
myshell> cat < input.txt

# Background execution
myshell> sleep 10 &
```

This implementation demonstrates fundamental operating systems concepts including process management, inter-process communication, and file I/O operations in a Unix environment.
## 👨‍💻 Author

**Yagna Gurram**

* GitHub: [YagnaGurram](https://github.com/YagnaGurram)
* Project Repo: [Custom Linux Shell](https://github.com/YagnaGurram/Custom-Linux-Shell-in-C)
