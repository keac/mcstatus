A Minecraft server status probing library written in C++

[![Build Status](https://travis-ci.org/MoeLeak/mcstatus.svg?branch=master)](https://travis-ci.org/MoeLeak/mcstatus)

![screenshot1](https://github.com/MoeLeak/mcstatus/blob/master/screenshot.png?raw=true)

# Building

On Debian/Ubuntu:
```
# apt-get install g++ cmake libboost-dev
$ mkdir build; cd build
$ cmake ..
$ make
```
On Arch Linux: 
```
# pacman -S gcc cmake boost
$ mkdir build; cd build
$ cmake ..
$ make
```

# Requirements
- C++11 compiler

# Examples

Check [this](https://github.com/MoeLeak/mcstatus/blob/master/example/src/main.cpp) out
