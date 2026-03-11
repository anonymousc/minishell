# Minishell

A minimal shell implementation written in C. Minishell replicates core features of **bash**, including command execution, pipes, redirections, environment variable expansion, and built-in commands.

## Features

- **Command Execution** – Run external binaries resolved via `$PATH`
- **Pipes** – Chain commands with `|`
- **Redirections** – Input (`<`), output (`>`), append (`>>`), and heredoc (`<<`)
- **Built-in Commands** – `cd`, `pwd`, `echo`, `export`, `env`, `unset`, `exit`
- **Environment Variables** – `$VAR` expansion and `$?` for the last exit status
- **Quote Handling** – Single quotes (literal) and double quotes (with expansion)
- **Signal Handling** – `Ctrl+C`, `Ctrl+D`, `Ctrl+\`
- **Memory Management** – Centralized garbage collector to prevent leaks

## Project Structure

```
.
├── main.c                  # Entry point – read, parse, execute loop
├── Makefile                # Build configuration
├── include/
│   └── minishell.h         # Type definitions and function declarations
├── parsing/
│   ├── lexer/              # Tokenization of input
│   ├── syntax/             # Syntax validation
│   ├── expansion/          # Environment variable and tilde expansion
│   └── parser/             # Build execution structures from tokens
├── execution/
│   ├── builtins/           # Built-in command implementations
│   ├── executer_core/      # Command execution engine
│   ├── heredoc/            # Heredoc processing
│   └── redirections/       # I/O redirection handling
└── others/
    ├── MiniLibc/           # Custom C library (strings, ctypes, printf)
    ├── garbage_collector/  # Memory tracking and cleanup
    ├── signals.c           # Signal handlers
    └── envadd.c            # Environment variable utilities
```

## Requirements

- **C compiler** – GCC or Clang
- **GNU Make**
- **readline library** – `libreadline-dev` (Debian/Ubuntu) or `readline` (macOS via Homebrew)

## Build

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and the executable
make re     # Full rebuild
```

## Usage

```bash
./minishell
```

Once running, minishell displays a prompt and accepts commands just like bash:

```
minishell$ echo "Hello, World!"
Hello, World!
minishell$ ls -la | grep .c | wc -l
1
minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
42
minishell$ exit
```

## Authors

- **Adil Essadik** – [aessadik@student.42.fr](mailto:aessadik@student.42.fr)
