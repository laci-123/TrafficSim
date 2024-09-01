# Assumes that Emscripten is on $PATH and all Emscripten environment variables are appropriately set.

CXX       = em++
CFLAGS    = -Wall -std=c++20 -c
LINKFLAGS = -s USE_GLFW=3 -s ASYNCIFY
INCLUDE	  = -I./raylib/src
LIBS	  = ./raylib/src/libraylib.a

index.js: obj/main.o obj/movable_point.o raylib/src/libraylib.a
	$(CXX) $(LINKFLAGS) $(LIBS) obj/main.o obj/movable_point.o -o index.js

raylib/src/libraylib.a:
	cd raylib/src && make PLATFORM=PLATFORM_WEB

obj:
	mkdir obj

obj/main.o: src/main.cpp src/movable_point.hpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/movable_point.o: src/movable_point.cpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@
