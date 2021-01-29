$(info +---------------------------------------------------------------------)
ifdef FIXTURES
else ifeq ($(shell uname -s),Linux)
  $(info | Environment detected as Linux/WSL)
  $(info | $(shell lsb_release -d))
  $(info +---------------------------------------------------------------------)
  $(info | If you get: error: invalid linker name in argument '-fuse-ld=lld')
  $(info | Run: )
  $(info | sudo apt-get update)
  $(info | sudo apt-get install lld)
  $(info +---------------------------------------------------------------------)
  CC=clang-11
  CXX=clang-11
  CFLAGS=-x c++ -c -Wall  -Wpedantic -Werror -std=c++17 $(INC_PARAMS) -g -D_GLIBCXX_DEBUG -O0 -fno-elide-constructors  -Wno-self-assign-overloaded
  LDFLAGS=-lstdc++ -lm -lncurses
endif

$(info | * compiler: $(CC))
$(info | * linker: $(CXX))
$(info | * home: $(HOME))
$(info +---------------------------------------------------------------------)

INCLUDE_DIRS= include
INC_PARAMS=$(foreach d, $(INCLUDE_DIRS), -I$d)

SRC:=$(shell find src -name '*.cpp')
OBJECTS=$(SRC:.cpp=.o)

APP_SRC=main.cpp
APP_OBJECTS=$(APP_SRC:.cpp=.o)
APP_EXECUTABLE=SnakeGame

all: $(SRC) $(APP_SRC) $(APP_EXECUTABLE)

$(APP_EXECUTABLE): $(APP_OBJECTS) $(OBJECTS)
	$(CXX) $(LDFLAGS) $(APP_OBJECTS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	-rm -f $(APP_EXECUTABLE)
	-rm -f $(ZIP_FILE)
	find . -name "*.gcda" -print0 | xargs -0 rm -f
	find . -name "*.gcno" -print0 | xargs -0 rm -f
	find . -name "*.o" -print0 | xargs -0 rm -f

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m