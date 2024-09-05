#ifndef CONTEXT_MENU_INCLUDED_
#define CONTEXT_MENU_INCLUDED_

#include "raylib.h"
#include "raymath.h"
#include <initializer_list>
#include <string>
#include <vector>
#include <functional>

class ContextMenu {
public:
  ContextMenu(std::initializer_list<std::string> entries);
  void update(float dt);
  void render() const;
  void show(Vector2 position);
  std::optional<size_t> selected_entry;
  std::vector<std::string> entries;
  bool visible;
private:
  std::optional<size_t> hovered_entry;
  std::vector<Rectangle> rectangles;
  int width;
};

#endif //CONTEXT_MENU_INCLUDED_
