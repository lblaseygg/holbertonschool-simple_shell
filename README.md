# Simple Shell Project

## Table of Contents
- [Description](#description)
- [Project Requirements](#project-requirements)
- [File Structure](#file-structure)
- [Tasks Overview](#tasks-overview)
- [How to Compile](#how-to-compile)
- [How to Use](#how-to-use)
- [Features](#features)
- [Examples](#examples)
- [Authors](#authors)

---

## Description
The **Simple Shell** project is a custom UNIX command-line interpreter written in **C programming language**. This project replicates a basic shell behavior by executing commands, handling errors, and enabling users to interact with their system through a simple prompt.

This program was developed as part of the curriculum at **Holberton School**, emphasizing system calls, process management, memory handling, and coding standards.

---

## Project Requirements
This project adheres to the following guidelines:
- Code follows **Betty coding style** (mandatory).
- Compiled on **Ubuntu 20.04 LTS** using:
  ```bash
  gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
  ```
- No use of standard libraries like `printf`, `malloc`, or advanced shell features initially.

---

## File Structure
Below is the structure of the repository:

| File                   | Description                                       |
|------------------------|---------------------------------------------------|
| `shell.c`              | Entry point of the shell program.                 |
| `main.h`               | Header file with prototypes and standard libraries.|
| `prompt.c`             | Manages the shell prompt display and input.      |
| `execute.c`            | Executes user-entered commands.                  |
| `builtins.c`           | Implements built-in commands like `exit` and `env`.|
| `helpers.c`            | Utility functions for parsing and error handling.|
| `man_1_simple_shell`   | Manual page for the custom shell.                 |
| `AUTHORS`              | File listing contributors to this project.       |

---

## Tasks Overview
Below is a summary of the core tasks completed in this project:

### 0. **README, man, AUTHORS**
- A comprehensive **README.md** explaining the project.
- A `man_1_simple_shell` manual page detailing usage.
- An `AUTHORS` file with a list of contributors.

### 1. **Betty would be proud**
- All code conforms to the **Betty coding style** standards.

### 2. **Simple shell 0.1**
- Display a prompt and wait for user commands.
- Execute simple commands using `execve`.
- Handle errors and **Ctrl+D** (EOF).
- Commands have no arguments, pipes, or advanced features.

### 3. **Simple shell 0.2**
- Extend version `0.1` to handle **commands with arguments**.

### 4. **Simple shell 0.3**
- Implement **PATH resolution** to locate and execute programs.
- Commands that do not exist will not fork unnecessary processes.

### 5. **Simple shell 0.4**
- Add built-in command `exit` to terminate the shell program.

### 6. **Simple shell 1.0**
- Add built-in command `env` to print the current environment variables.

---

## How to Compile
To compile all the files and produce the `hsh` executable, use:
```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```
---

## How to Use
### Interactive Mode
1. Run the shell program:
    ```bash
    ./hsh
    ```
2. A custom prompt (`$`) appears. Type commands:
    ```bash
    $ /bin/ls
    file1 file2 simple_shell
    $ exit
    ```

### Non-Interactive Mode
Execute a command via piping:
```bash
echo "/bin/ls" | ./hsh
```
---

## Features
- Display a shell prompt.
- Execute UNIX commands with or without arguments.
- Resolve commands using the PATH variable.
- Handle built-in commands:
    - **`exit`**: Exit the shell.
    - **`env`**: Print the current environment.
- Handle end-of-file condition (Ctrl+D).
- Error handling for invalid commands.

---

## Examples
### Interactive Example
```bash
$ ./hsh
$ /bin/ls
file1 file2 simple_shell
$ exit
```

### Non-Interactive Example
```bash
echo "/bin/ls" | ./hsh
file1 file2 simple_shell
```
---

## Authors
- **Luis Feliciano** - [Luis' GitHub](https://github.com/lblaseygg)
- **Tommy Hernandez** - [Tommy's GitHub](https://github.com/TommyBryan)

---
