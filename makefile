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
build/index.js: obj/assets.o obj/road_network.o obj/main.o obj/context_menu.o obj/bezier_curve.o obj/movable_point.o obj/road_segment.o raylib/src/libraylib.a | build
	$(CXX) $(LINKFLAGS) $^ --preload-file ./assets -o build/index.js

build/index.html: src/index.html | build
	cp $< $@

raylib/src/libraylib.a:
	cd raylib/src && make PLATFORM=PLATFORM_WEB CUSTOM_CFLAGS="-DSUPPORT_FILEFORMAT_SVG"

obj:
	mkdir obj

build:
	mkdir build

obj/main.o: src/main.cpp src/road_network.hpp src/assets.hpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/movable_point.o: src/movable_point.cpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/bezier_curve.o: src/bezier_curve.cpp src/movable_point.hpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/road_segment.o: src/road_segment.cpp src/bezier_curve.hpp src/context_menu.hpp src/road_network.hpp src/assets.hpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/context_menu.o: src/context_menu.cpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/road_network.o: src/road_network.cpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/assets.o: src/assets.cpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

