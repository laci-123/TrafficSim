# Assumes that Emscripten is on $PATH and all Emscripten environment variables are appropriately set.

CXX        = em++
CFLAGS     = -Wall -Wextra -std=c++20 -c
DEPFLAGS   = -MM
INCLUDE	   = -isystem ./raylib/src
LINKFLAGS  = -s USE_GLFW=3 -s ASYNCIFY
LIBS       = raylib/src/libraylib.a
ASSETS_DIR = ./assets/
ASSETS     = $(wildcard $(ASSETS_DIR)/*)
SRC        = src
BUILD      = build
OBJ        = build/obj
DEP        = build/dependencies
SRC_FILES  = $(wildcard $(SRC)/*.cpp)
OBJ_FILES  = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRC_FILES))
DEP_FILES  = $(patsubst $(SRC)/%.cpp, $(DEP)/%.d, $(SRC_FILES))

all: $(BUILD)/index.js $(BUILD)/index.html

clean:
	rm -rf $(BUILD)
	rm -rf $(OBJ)
	rm -rf $(DEP)

.PHONY: all clean

# disable all built-in implicit rules
.SUFFIXES:

$(BUILD)/index.js: $(OBJ_FILES) $(LIBS) $(ASSETS) | $(BUILD)
	$(CXX) $(LINKFLAGS) $(OBJ_FILES) $(LIBS) --preload-file $(ASSETS_DIR) -o $(BUILD)/index.js

$(BUILD)/index.html: $(SRC)/index.html | build
	cp $< $@

raylib/src/libraylib.a:
	cd raylib/src && make PLATFORM=PLATFORM_WEB CUSTOM_CFLAGS="-DSUPPORT_FILEFORMAT_SVG"

$(OBJ):
	mkdir -p $(OBJ)

$(BUILD):
	mkdir -p $(BUILD)

$(DEP):
	mkdir -p $(DEP)

$(OBJ)/%.o: $(SRC)/%.cpp $(DEP)/%.d | $(OBJ)
	$(CXX) $(CFLAGS) $(INCLUDE) $< -o $@

# This is needed to prevent depndency files to be marked as "intermediate".
# Intermediate files are automatically removed, which we don't want to happen.
$(DEP_FILES):

$(DEP)/%.d: $(SRC)/%.cpp | $(DEP)
	$(CXX) $(INCLUDE) $(DEPFLAGS) $< | sed 's#\(.*\)\.o:#obj/\1.o:#' > $(DEP)/$*.d

include $(wildcard $(DEP)/*.d)
