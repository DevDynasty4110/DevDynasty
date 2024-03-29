# executable file name
PROJECT = sudoku

EXECUTABLE := $(PROJECT).exe

# which compiler
CXX := g++

#define paths
WX_CONFIG = wx-config
WX_FLAGS = $(shell wx-config --cxxflags)
WX_LIBS = $(shell wx-config --libs)
OBJ_PTH = obj
SRC_PTH = src
INCLUDE_PTH = include

#generate obj/ dir if missing:

$(shell mkdir -p $(OBJ_PTH))


# variables for our source and header files
SRC_FILES := $(wildcard $(SRC_PTH)/*.cpp)
HEADER_FILES := $(wildcard $(INCLUDE_PTH)/*.h)

# variable for intermediate binary files (.o files)
OBJ_FILES := $(patsubst $(SRC_PTH)/%.cpp,$(OBJ_PTH)/%.o,$(SRC_FILES))

# flags for the compiler
LDFLAGS = -g -ggdb -static-libstdc++ -std=gnu++17 -Wall -Wextra -pedantic
CPPFLAGS = -g -ggdb -static-libstdc++ -std=gnu++17 -Wall -Wextra -pedantic

# command run to build the executable
${EXECUTABLE}: $(OBJ_FILES) 
	${CXX} -o $@ $(OBJ_FILES) $(LDFLAGS) $(WX_LIBS) $(WX_FLAGS)
# command run to compile our .cpp files to .o binaries
$(OBJ_PTH)/%.o: $(SRC_PTH)/%.cpp
	${CXX} -c -o $@ $(WX_FLAGS) $(CPPFLAGS) $<

clean:
	rm -rf $(OBJ_PTH) *.out *.exe $(EXECUTABLE)
cleanWin:
	del /Q /F $(OBJ_PTH)/*.o *.out *.exe $(EXECUTABLE)

test:
	make clean
	make
	./$(EXECUTABLE)