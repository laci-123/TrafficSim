# Assumes that Emscripten is on $PATH and all Emscripten environment variables are appropriately set.

CXX        = em++
CFLAGS     = -Wall -Wextra -std=c++20 -c
LINKFLAGS  = -s USE_GLFW=3 -s ASYNCIFY
INCLUDE	   = -isystem ./raylib/src
LIBS       = raylib/src/libraylib.a
ASSETS_DIR = ./assets/
ASSETS     = $(wildcard $(ASSETS_DIR)/*)
#            cannot use a wildcard here because these files potentially do not exist yet
OBJ_FILES  = obj/game.o \
	     obj/toolbox.o \
             obj/intersection.o \
             obj/assets.o \
             obj/road_network.o \
             obj/main.o \
             obj/context_menu.o \
             obj/bezier_curve.o \
             obj/movable_point.o \
             obj/road_segment.o \
             obj/dragable.o


all: build/index.js build/index.html

clean:
	rm -rf obj
	rm -rf build

.PHONY: all clean

build/index.js: $(OBJ_FILES) $(LIBS) $(ASSETS) | build
	$(CXX) $(LINKFLAGS) $(OBJ_FILES) $(LIBS) --preload-file $(ASSETS_DIR) -o build/index.js

build/index.html: src/index.html | build
	cp $< $@

raylib/src/libraylib.a:
	cd raylib/src && make PLATFORM=PLATFORM_WEB CUSTOM_CFLAGS="-DSUPPORT_FILEFORMAT_SVG"

obj:
	mkdir obj

build:
	mkdir build

obj/main.o: src/main.cpp src/game.hpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/movable_point.o: src/movable_point.cpp src/dragable.hpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/bezier_curve.o: src/bezier_curve.cpp src/movable_point.hpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/road_segment.o: src/road_segment.cpp src/bezier_curve.hpp src/context_menu.hpp src/road_network.hpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/context_menu.o: src/context_menu.cpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/road_network.o: src/road_network.cpp src/assets.hpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/assets.o: src/assets.cpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/intersection.o: src/intersection.cpp src/road_network.hpp src/dragable.hpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/toolbox.o: src/toolbox.cpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/game.o: src/game.cpp src/assets.hpp src/toolbox.hpp src/road_network.hpp src/road_segment.hpp src/intersection.hpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

obj/dragable.o: src/dragable.cpp | obj
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

