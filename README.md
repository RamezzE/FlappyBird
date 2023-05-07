# FlappyBird
Flappy Bird clone.

Written in C++ using the SFML graphics library

![FlarkyBird](https://user-images.githubusercontent.com/117018553/236696518-741fac19-3518-4637-8434-b4b73689310d.gif)

## Controls:
- *Space* or *Left Mouse Click* to jump
- *R* to restart
- *Esc* to pause

## Prerequisites

- SFML 2.5.1 or above www.sfml-dev.org

#### Linux

- g++ 4.8 or above

- You can run this command on linux to install SFML

```
$ sudo apt-get install libsfml-dev
```

#### MS Build
 - Visual Studio 15 or above
 - VC++ 15 or above


## Building

### GNU Make (Method used)

- Install GNU Make on your device

- Download source code

- Edit the Makefile in the project directory to to add your SFML/include & SFML/lib paths

- Open your terminal in your project directory where the Makefile exists

- Run Make in your terminal:

```
$ make clean
$ make
```

### MS Build 

 1. Add the `</path/to/sfml/>/include` to your **additional C++ include directories**.
 2. Add `</path/to/sfml/>/lib` to your **additional library directories**.
 3. Add the SFML libraries used to your **additional dependencies** 
 
    eg: 
     ``
     sfml-graphics.lib;sfml-system.lib;sfml-window.lib;
     ``
 
 4. Add the dlls in your SFML path/bin along with your executable
 

### To build SFML statically 
  Add the following libraries to your **additional dependencies**
  
  ``
  sfml-graphics-s-d.lib sfml-window-s-d.lib sfml-system-s-d.lib opengl32.lib winmm.lib gdi32.lib sfml-main-d.lib freetype.lib
  ``
  
  You can remove the ``-d`` if you do not need to debug
  
## Acknowledgements

This clone is inspired by this tutorial series https://www.youtube.com/watch?v=KNvRFEDQpOA&list=PLRtjMdoYXLf7DB3--POF9lYzaZu0poT5V

## License

This project is licensed under the MIT license
