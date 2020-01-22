# ft_select
![ft_select screeneshot](https://sun9-63.userapi.com/c205228/v205228503/450f0/PjYiB7A8hao.jpg)
# About
ft_select is the third project of the Unix branch at 42. The goal for this project is to learn more about screen oriented programs using termcap/terminfo libraries in the C programming language. It's originally just an argument viewer in the terminal but I decided to take it one step further and gave it browsing capabilities on the file system.

The main goal, however, is to build my own functional shell. Something like zsh and bash, this is what the next project at my school is about and ft_select is just a small part of it.
# Building
1. Download/Clone this repo
```
git clone https://github.com/TheWeaklessOne/ft_select.git
```
2.`cd` into the root directory and run `make`
```
cd ft_select
make
```
3. Run
```
./ft_select * 1 2 3
```
![ft_select output](https://sun9-58.userapi.com/c205228/v205228503/450fa/uspolS890_w.jpg)
# Project instructions
* Project must be written in C in accordance with the Norm.
* Program cannot have memory leaks.
* No Segmentation fault, bus error, double free, etc.
* Within the mandatory part, you are allowed to use only the following libc functions:
  - isatty, ttyname, ttyslot
  - ioctl
  - getenv
  - tcsetattr, tcgetattr
  - tgetent, getflag, tgetnum, tgetstr, tgoto, tputs
  - open, close, write
  - malloc, free
  - read, exit
  - signal
* You can move through the list of arguments using arrows
* Exits on `ESC` key
* Press `+` to select all and `-` to unselect all
* Handles interruption signals gracefully (ctrl + z, ctrl + c, kill, etc...)
* Restores the screen to what it was before clearing it.
