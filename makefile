# Assumes that Emscripten is on $PATH and all Emscripten environment variables are appropriately set.

CXX       = em++
CFLAGS    = -Wall -std=c++20 -c
LINKFLAGS = -s USE_GLFW=3 -s ASYNCIFY
INCLUDE	  = -I./raylib/src

all: build/index.js build/index.html

clean:
	rm -rf obj
	rm -rf build

.PHONY: all clean

#		cannot use a wildcard here because these files potentially do not exist yet
build/index.js: obj/main.o obj/bezier_curve.o obj/movable_point.o raylib/src/libraylib.a | build
	$(CXX) $(LINKFLAGS) $^ -o build/index.js

build/index.html: src/index.html | build
	cp $< $@

raylib/src/libraylib.a:
	cd raylib/src && make PLATFORM=PLATFORM_WEB

obj:
	mkdir obj

build:
	mkdir build

obj/main.o: src/main.cpp src/bezier_curve.hpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/movable_point.o: src/movable_point.cpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/bezier_curve.o: src/bezier_curve.cpp src/movable_point.hpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@
