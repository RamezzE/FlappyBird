# FlappyBird
Flappy Bird clone.

Written in C++ using the SFML graphics library

![FlarkyBird](https://user-images.githubusercontent.com/117018553/236696518-741fac19-3518-4637-8434-b4b73689310d.gif)

## Controls:
- *Space* or *Left Mouse Click* to jump
- *R* to restart
- *Esc* to pause

## Prerequisites
- g++ 4.8 or above
- GNU Make
- SFML 2.5.1 or above [[www.sfml-dev.org](https://www.sfml-dev.org/download/sfml/2.5.1/)]

### Linux
- You can run these commands on linux to install g++, Make and SFML

```
$ sudo apt-get install g++
$ sudo apt-get install make
$ sudo apt-get install libsfml-dev
```

### Windows
- Install the proper SFML version from the website (MinGW version for GNU Make build or Visual C++ for MS Build)
- Unzip the SFML downloaded folder ( You can install 7zip to be able to unzip )

#### GNU Make
- Install GNU Make by installing [chocolatey](https://chocolatey.org/install#individual) package manager  and running this command from an elevated Command Prompt:
```
$ choco install make
```
- Install MinGW g++ [MinGW 32-bit](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z/download) or [MinGW 64-bit](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-posix/seh/x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z/download) (The SFML version and the MinGW version have to match)

- After unzipping the MinGW file, add your path to mingw32/bin or mingw64/bin to PATH in the system environmental variables

- Edit the ```SFML_DIR``` in the Makefile to add your correct SFML folder or copy the folder to the project directory and name the folder 'SFML'

#### MS Build
- Visual Studio 15 or above
- VC++ 15 or above


## Building

### GNU Make (Method used)

- Download source code

- Open your terminal in your project directory where the Makefile exists

- Run Make in your terminal:

```
$ make
```

- List of make commands you can use
```
# Build and run in release mode
$ make

# Build and run in debug mode
$ make debug && make run

# Rebuild in release or debug mode
$ make rebuild

# or 
$ make rebuild-debug

# Clean the files
$ make clean

# Run the latest compiled build
$ make run
```

### MS Build

1. Add the `</path/to/sfml_folder/>/include` to your **additional C++ include directories**.
2. Add `</path/to/sfml_folder/>/lib` to your **additional library directories**.
3. Add the SFML libraries used to your **additional dependencies**

   eg:
   ``
   sfml-graphics.lib;sfml-system.lib;sfml-window.lib;sfml-audio.lib;
   ``

4. Add the dlls in your SFML path/bin along with your executable

  
## Acknowledgements

This clone is inspired by this tutorial series by [Sonar Systems](https://www.youtube.com/watch?v=KNvRFEDQpOA&list=PLRtjMdoYXLf7DB3--POF9lYzaZu0poT5V)

## License

This project is licensed under the MIT license
