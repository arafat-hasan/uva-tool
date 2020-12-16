uva-tool
===================


[![Build Status](https://travis-ci.org/arafat-hasan/uva-tool.svg?branch=master)](https://travis-ci.org/arafat-hasan/uva-tool)
![GitHub](https://img.shields.io/github/license/arafat-hasan/uva-tool.svg)
![GitHub issues](https://img.shields.io/github/issues/arafat-hasan/uva-tool.svg)
![GitHub stars](https://img.shields.io/github/stars/arafat-hasan/uva-tool.svg?style=social&label=Stars)
[![AUR version](https://img.shields.io/aur/version/uva-tool-git?logo=Arch-Linux)](https://aur.archlinux.org/packages/uva-tool-git/)


Command Line Based Tool for [uva onlinejudge](https://uva.onlinejudge.org/) with features Submitting and uHunting.


## Dependency
- Command line based tool [`curl`](https://curl.haxx.se/)


## External Libraries
- [`nlohmann json`](https://github.com/nlohmann/json) C++ library


## Installation
General installation process is only available for Linux operating system, Windows version is coming soon. But now, you can use this tool in windows by changing some lines of source code.

- **Install `curl`:** Download and install [curl](https://github.com/curl/curl) (website: https://curl.haxx.se/). On ubuntu to install curl execute  

```sh
sudo apt install curl
```
- **Download uva-tool:** Execute command

```sh
git clone https://github.com/arafat-hasan/uva-tool.git
```
- **Install uva-tool:** In the downloaded folder `uva-tool`, look for `install.sh` file and execute it (C++ compiler needed here, GNU g++ used in testing).  

```sh
chmod +x install.sh 
./install.sh
```


## Troubleshooting
Your system may not able to use `getlogin()` function which is used in `src/uva-tool.cpp` file for `szHome` constant. In that case set `szHome` constant to your operating system's username.

Get you login username using command `whoami` or `echo $USERNAME`.

Now set szHome const
```cpp
const string szHome = "username";
```


## Usage Example
Run corresponding commands

- **Login:** `uva-tool -login`
- **Logout:** `uva-tool -logout`
- **Hunt:** `uva-tool -hunt -u felix_halim -r 10`  
This will show last 10 submissions of user `felix_halim`
- **Submit:** Syntax `uva-tool -submit problem_number problem_path language`  
Example `uva-tool -submit 100 ~/Desktop/100.cpp 5`  
This will submit `100.cpp` named file from Desktop directory in C++11 (5 for C++11) language with problem number 100.

> **Note:**
> Language codes *1 for ANSI, 2 for JAVA, 3 for C++, 4 for Pascal, 5 for C++11, 6 for Python*.



## Integrate with VIM
Copy `vim_uva-tool_run_script.sh` file to your .vim directory and add this lines to .vimrc file
```
map <leader>uvw :!clear && uva-tool -hunt -u felix_halim -r 10
map <leader>uvs :!clear && ~/.vim/vim_uva-tool_run_script.sh '%:p'<CR>
map <leader>uvi :!uva-tool -login
map <leader>uvo :!uva-tool -logout
```

**Keyboard mappings**  
`\uvs` to submit  
`\uvw` to hunt  
`\uvi` to login  
`\uvo` to logout  




## Integrate with Geany

Copy `geany_uva-tool_run_script.sh` file to `/home/$USER/.config/geany/uva-tool` directory and run command `chmod +x geany_uva-tool_run_script.sh`.

Now in geany (open a file i.e a **cpp** file first), go to *Build -> Set Build Commands*, a window opens. In *Execute commands* section at no 2, set this Command, Working directory and Label  
**Command:** `./geany_uva-tool_run_script.sh  '%f'  '%d'`  
**Working directory:** `/home/$USER/.config/geany/uva-tool`  
**Label:** `uva-tool`  


Now all set.  
Click on *Build -> uva-tool* for submitting, huntting etc.  

It's not a good idea to run a script in command execution section of geany for running uva-tool instead of writing a geany plugin, but a easy good hack. And I have no plan to write a geany plugin for that in future. Anyone who interested, warmly welcomed with MIT licenses.



## To Do

- Bring Windows version
- Show user statistics in hunting
- Use a C++ networking library instead of cURL
- Make command line options more dynamic

