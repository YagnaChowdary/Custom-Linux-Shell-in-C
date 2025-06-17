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
   git clone https://github.com/your-username/custom-linux-shell.git
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

## 📌 Notes

* Only supports basic job backgrounding (no `jobs`, `fg`, `bg` yet)
* More advanced features like globbing or scripting are not yet implemented

---

## 📚 Dependencies

* GCC
* GNU Readline (`libreadline-dev` on Linux)

Install Readline if not present:

```bash
sudo apt install libreadline-dev
```

---

## 📄 License

This project is licensed under the MIT License.
# custom-linux-shell
This is a complete implementation of a custom Unix shell written in C called "myshell". Here's what this shell provides:

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
