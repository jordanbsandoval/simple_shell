# Simple Shell
==============

! [Shell_holberton](./img/shell.png "shell-logo")

Project from Holbeton School that consist on create a simple shell in C language that is able to excute basic system commands.

## How to use this repo

1. Clone the repo
```
git clone https://github.com/jordanbsandoval/simple_shell.git 
```

2. Compile your program
```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

3. Testing

## interactive mode

```
$ ./hsh hsh$ /bin/ls hsh main.c shell.c hsh$ hsh$ exit $
```
## Non-interactive mode
```
$ echo "/bin/ls" | ./hsh hsh main.c shell.c $
```
If your ./hsh fails because permissions, remember to chmod +x that file


