 #
 # Author: KK <thumbd03803@gmail.com>
 #
 # File: Makefile
 #

CXX = g++
CXXFLAG = -Wall -g -std=c++11

SRC_PATH = $(PWD)/src

# Include flags
INCLUDE = -I $(PWD)/include

# Libs flags
LIB += $(shell pkg-config --libs openal)
LIB += $(shell pkg-config --libs alure)
LIB += $(shell pkg-config --libs sdl2)
LIB += $(shell pkg-config --libs ncurses)

# Object files
OBJ_PATH = $(PWD)/obj
OBJ = $(PWD)/obj/main.o \
      $(PWD)/obj/gpio.o \
      $(PWD)/obj/soundEngine.o \
      $(PWD)/obj/sound.o

DEBUG_OBJ = $(PWD)/obj/test.o \
	    $(PWD)/obj/gpio.o \
	    $(PWD)/obj/soundEngine.o \
	    $(PWD)/obj/sound.o \
	    $(PWD)/obj/chord.o

OUT_EXE = air
DEBUG_OUT_EXE = air_debug

# This one is used for testing on PC
test: $(DEBUG_OUT_EXE)

# This one is used on real Rpi
real: $(OUT_EXE)

$(OUT_EXE): $(OBJ)
	@echo "    LD    " $(notdir $@)
	@$(CXX) $(OBJ) $(CXXFLAG) $(LIB) -o $@

$(DEBUG_OUT_EXE): $(DEBUG_OBJ)
	@echo "    LD    " $(notdir $@)
	@$(CXX) $(DEBUG_OBJ) $(CXXFLAG) $(LIB) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@echo "    CC    " $(notdir $@)
	@$(CXX) -c $< $(CXXFLAG) $(INCLUDE) -o $@

.PHONY: clean
clean:
	@rm -frv $(OBJ) $(OUT_EXE) $(DEBUG_OUT_EXE)
