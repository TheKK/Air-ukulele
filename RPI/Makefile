 #
 # Author: KK <thumbd03803@gmail.com>
 #
 # Makefile
 #

CXX = g++
CXXFLAG = -Wall -g -std=c++11

SRC_PATH = $(PWD)/src

# Include flags
INCLUDE = -I $(PWD)/include

# Libs flags
LIB += $(shell pkg-config --libs openal)
LIB += $(shell pkg-config --libs freealut)

# Object files
OBJ_PATH = $(PWD)/obj
OBJ = $(PWD)/obj/main.o \
      $(PWD)/obj/gpio.o

OUT_EXE= air

all: $(OUT_EXE)

$(OUT_EXE): $(OBJ)
	@echo "    LD    " $(notdir $@)
	@$(CXX) $(OBJ) $(CXXFLAG) $(LIB) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@echo "    CC    " $(notdir $@)
	@$(CXX) -c $< $(CXXFLAG) $(INCLUDE) -o $@

.PHONY: clean
clean:
	@rm -frv $(OBJ) $(OUT_EXE)
