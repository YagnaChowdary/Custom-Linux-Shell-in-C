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
