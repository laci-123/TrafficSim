# Assumes that Emscripten is on $PATH and all Emscripten environment variables are appropriately set.

SRC      = ./src
COMPILER = em++
CFLAGS   = -Wall -Wextra
EMFLAGS	 = -s USE_GLFW=3 -s ASYNCIFY
INCLUDE	 = -I./raylib/src
LIBS	 = ./raylib/src/libraylib.a

index.js: $(SRC)/main.cpp
	$(COMPILER) $(CFLAGS) $(EMFLAGS) $(INCLUDE) $(LIBS) main.cpp -o index.js
