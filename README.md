# Thema assignment - Devices
The Universtity of applied sciences Utrecht ([HU](https://www.hu.nl/)) provided their students with the assignment to create a simple lasertag game in small teams. This repository provides the implementation made by the team of [Casper](https://github.com/CasperTI), [Robert](https://github.com/riberts), and [me](https://github.com/MatthijsMud).

Arduino Dues are used to realise the laserguns which the players use while playing. Each of the laserguns has an IR Led that is used as a laser. An IR receiver is used to detect whether a player is hit.

As this is a school assignment, no pull requests will be accepted (unless it is one made by one of the teammembers listed prior).

## Getting started
Open a console and clone this repository using the following commands. The last line is needed to download the submodules, which aren't downloaded by default.
```git
git clone git://github.com/MatthijsMud/Themaopdracht-Devices.git
cd Themaopdracht-Devices
git submodule update --init --recursive
```
[BPMTK](https://github.com/wovo/bmptk) comes with a custom toolchain for Makefiles. Please make sure to use it instead of the standard make command that comes with a package like MinGW. It should be located in `bmptk/tools/bmptk-make.exe` (relative from where the Makefile is). BMPTK's homepage contains notes for running it on Linux.

As noted before, this project is intended to run on an Arduino Due. A toolchain is needed to upload to its chip, which is not installed by default. See [GNU toolchains](http://gnutoolchains.com/arm-eabi/) for for the `arm-eabi` installer, which is needed to run this project.

Try to run the examples in `hwlib/demo/arduino-due` to make sure everything is installed correctly. You might need to update the COM port in the relevant Makefile before running `bmptk-make`.  

## Other students
For other students of the HU that might stumble on this repository, please note that the goal of the assigment is to learn implement a realtime system. You will probably learn less from copying from this repository, so you miss out on the goal of the assignment. Not to mention the fact that it could be considered plagiatry, which will (most likely) result in bad grades.
