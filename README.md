# MiniShell

This project is a simplistic implementation of a Linux console, called MiniShell. It provides basic functionality such as executing commands, changing directories, listing files, and running programs. The project is written in C programming language and utilizes various system libraries.

## Commands

The MiniShell supports the following commands:

- `hola`: Prints "Hola!" to the console.
- `exit`: Exits the MiniShell.
- `clear`: Clears the console.
- `ls`: Lists files and directories in the current directory. Directories are displayed in blue text, while files are displayed in red text.
- `cd [directory]`: Changes the current directory. Requires an argument specifying the target directory.
- `list`: Lists all available commands.
- `run [program]`: Runs a program specified by the user. Requires an argument specifying the program path, followed by any additional arguments.

## Compiling the Project

- C compiler (e.g., GCC)

- `gcc minishell.c -o minishell`

- `./minishell`
