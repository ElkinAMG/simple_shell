# SHELL PROJECT - A BASIC SHELL "RE-CREATION"

![](img/giphy.gif)

### Objectives
- This project was developed for learning purpose.
- Recreate a command interpreter. Shells are designed to facilitate the way in which the different programs available on the computer are invoked or executed.

### files contained in the project:

| File | Description |
| ------ | ------ |
| main.c | contain the main function that excute the shell. |
| find_commands.c | Contain functions to executes the given command. |
| recognize_command.c | Cotain functions that cut the command and pass it to checker and print error when if exits. |
| shell.h | This is a static library containing prototypes and directives. |
| strings_utilities.c | Cotains functions to compare strings, know the lengh of strings, copy the strings. |
| utilities.c | Cotains functions to allocate the necesarry bytes in memory and break it free. |
| man_1_simple_shell | This is our function manual v.0.0.1. |

## Compilate and run tests

You can use any of the ```main.c``` found in the [test](./test) folder.

Files are compiled this way:

```
$ gcc -Wall -Wno-format -Werror -Wextra -pedantic *.c
$ ./a.out
```

### Authors
- Yoyman Castellar - [Github](https://github.com/ymcastellar) , [Twitter](https://twitter.com/castellaryoyman).
- Elkin Mejia - [Github](https://github.com/ElkinAMG) , [Twitter](https://twitter.com/ElkinAMG).

###  End of README.md