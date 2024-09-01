# Assumes that Emscripten is on $PATH and all Emscripten environment variables are appropriately set.

COMPILER = em++
CFLAGS   = -Wall -Wextra
EMFLAGS	 = -s USE_GLFW=3 -s ASYNCIFY
INCLUDE	 = -I./raylib/src
LIBS	 = ./raylib/src/libraylib.a

index.js: src/main.cpp raylib/src/libraylib.a
	$(COMPILER) $(CFLAGS) $(EMFLAGS) $(INCLUDE) $(LIBS) src/main.cpp -o index.js

raylib/src/libraylib.a:
	cd raylib/src && make PLATFORM=PLATFORM_WEB
