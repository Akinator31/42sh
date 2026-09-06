# 42sh

Unix shell written in C, developed as a group project as part of the Epitech curriculum. `42sh` builds on the Minishell1 and Minishell2 projects, extending them into a more complete shell inspired by TCSH.

## Description

Binary name: `42sh`. The reference shell for syntax and behavior is `tcsh`. On top of simple command execution, sequencing, pipes, and redirections, `42sh` adds interactive line editing, command history, aliases, subshells, and command substitution.

## Features

- Everything from Minishell1 and Minishell2: builtins, resolution via `PATH`, environment handling, sequencing with `;`, pipes `|`, and redirections `>`, `>>`, `<`
- Subshells using parentheses `( )`
- Command substitution with backticks `` ` ``
- Single-quote inhibitors (`'`) to escape special characters in a command
- Environment variable expansion (`$VAR`)
- Interactive line editing in raw terminal mode: cursor movement and line redrawing
- Command history with arrow-key navigation, persisted to a history file
- Aliases loaded from a `~/.42shrc` configuration file at startup, and manageable at runtime with the `alias` builtin
- A bonus seccomp-based wrapper that launches `42sh` with `fork`, `vfork` and `clone` blocked, to run it in a restricted environment
- Error handling on standard error, with an exit code matching the executed command's exit status

## Builtins

| Command | Description |
|---|---|
| `cd [directory]` | Changes the current directory. Without argument, moves to `HOME`. Also supports `~` and `-` |
| `env` | Prints the current environment variables, no argument |
| `setenv [name] [value]` | Creates or updates an environment variable |
| `unsetenv name` | Removes an environment variable (the `*` wildcard is not supported) |
| `exit` | Exits the shell |
| `history` | Prints the command history |
| `repeat n command` | Runs `command` `n` times |
| `alias [name] [command]` | Without argument, lists all aliases; with one argument, shows a given alias; with two, defines a new alias |
| `where command` | Lists every matching binary found in `PATH` |
| `which command` | Prints the path of the first matching binary found in `PATH` |

## Command parsing order

A command line goes through the following stages, in order:

1. Subshell detection (`( )`)
2. Backtick command substitution
3. Splitting and sequential execution of commands separated by `;`
4. Redirections (`>>`, then `>`)
5. Pipes `|`
6. Redirection (`<`)
7. Builtin lookup
8. External binary execution

## Compilation

The project is built with `make`, using a Makefile that provides the following rules:

```bash
make            # builds the 42sh binary
make debug      # builds a debug version with AddressSanitizer
make tests_run  # builds and runs the unit tests (Criterion)
make show_test  # runs the tests and generates an HTML coverage report
make clean      # removes object files
make fclean     # removes object files, binaries and generated reports
make re         # fclean then full rebuild
```

## Usage

Interactive mode:

```bash
./42sh
```

Interactive mode enables raw-mode line editing, history navigation with the arrow keys, aliases, and command substitution.

Non-interactive mode:

```bash
echo "ls -l | wc -l" | ./42sh
```

The shell exits with `exit`, or with `EOF` (Ctrl+D) in interactive mode.

## Configuration

On startup, `42sh` looks for a `~/.42shrc` file to load aliases, for example:

```
alias ls = ls --color
```

## Exit codes

The shell returns the exit code of the last executed command, matching `tcsh` behavior. On an internal error (command not found, invalid argument, builtin error, malformed redirection), the exit code is 84.

## Project structure

```
.
├── bonus/          seccomp-based restricted execution wrapper
├── include/        project headers
├── lib/            reimplemented basic utility functions
├── src/
│   ├── 42rc/       loading of the ~/.42shrc configuration file and aliases
│   ├── commands/   builtins and execution of external commands
│   ├── history/    command history storage and navigation
│   ├── line_buffer/  in-memory representation of the line being edited
│   ├── terminal/   raw terminal mode and interactive line editing
│   ├── utils/      command parsing, pipes, redirections, semicolons,
│   │               subshells, backticks, environment handling
│   └── main.c      program entry point
├── tests/          unit tests (Criterion)
└── Makefile
```

## Not implemented

The following features, listed as possible additions in the Epitech subject, are not implemented in this project: globbing (`*`, `?`, `[`, `]`), job control (`&`, `fg`, `bg`), local shell variables, special variables (`term`, `precmd`, `cwdcmd`, `cwd`, `ignoreof`), tab-completion, and scripting.

## Tests

Unit tests are written with Criterion and located in the `tests/` directory. They can be run with `make tests_run`, and a coverage report can be generated with `make show_test`.

## Authors

Project developed by [@Akinator31](https://github.com/Akinator31), [@Nogo4](https://github.com/Nogo4), [@tictacgame](https://github.com/tictacgame) and [@Arkcadia](https://github.com/Arkcadia).
