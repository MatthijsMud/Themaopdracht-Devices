#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################


RELATIVE          ?= ./hwlib
RTOS              ?= ./rtos
SOURCES :=        

# header files in this project
HEADERS :=

# other places to look for files for this project
SEARCH  := 
HEAP := BMPTK

# common settings for Arduino Due projects
TARGET            ?= arduino_due
SERIAL_PORT       ?= COM3
CONSOLE_BAUDRATE  ?= 2400

include $(RTOS)/makefile.inc
include $(RELATIVE)/makefile.link
