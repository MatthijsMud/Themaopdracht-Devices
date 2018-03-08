#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
#
#############################################################################

# Listing of the files which should be compiled for this project. Don't forget
# to add any newly created file to this listing (if it needs to get compiled).
SOURCES := Keypad.cpp EventHandler.cpp GameController.cpp GameParameterController.cpp SendIRController.cpp 
HEADERS := Keypad.hpp EventHandler.hpp GameController.hpp EventSource.hpp KeypadListener.hpp IRListener.hpp

# Paths in which the compiler will search for files that are included.
# This to avoid very long include paths.
SEARCH  :=

# Indacates we want to use a heap in our application.Please note that chosen
# implementation is very simple, and does not support the release of memory.
# It is only needed for RTOS, which invokes new.
HEAP    := BMPTK

# Common settings for Arduino Due projects
TARGET            ?= arduino_due
CONSOLE_BAUDRATE  ?= 2400

# When test-running this project, the arduino connected to this port. This might
# not be true for everyone, so oyu might need to look into hwlib/makefile.local
# for a solution, as not to change this file with each commit.
SERIAL_PORT       ?= COM3

# RTOS' included makefile adds itself to the search directories. But it needs to
# know where it is located; this directive is used as an indication.
RTOS              ?= ./rtos
include $(RTOS)/makefile.inc

# Hwlib makes usage of the RELATIVE directive to determine where its located
# relative to the makefile that included it. This is required for the paths it
# generates.
RELATIVE          ?= ./hwlib
include $(RELATIVE)/makefile.link
