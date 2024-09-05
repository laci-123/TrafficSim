#include "context_menu.hpp"


static constexpr int FONT_SIZE   = 14;
static constexpr int PADDING     = 4;
static constexpr int RECT_HEIGHT = FONT_SIZE + 2 * PADDING;

ContextMenu::ContextMenu(std::initializer_list<std::string> entries) 
  :entries{entries}
{
  this->calculate_width();
}

void ContextMenu::update(float dt) {
  if(!this->visible) {
    return;
  }
  
  Vector2 mouse = GetMousePosition();
  this->hovered_entry = {};
  for(size_t i = 0; i < this->rectangles.size(); ++i) {
    if(CheckCollisionPointRec(mouse, this->rectangles[i])) {
      this->hovered_entry = i;
      if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        this->selected_entry = i;
        this->visible = false;
      }
    }
    else {
      if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        this->visible = false;
      }
    }
  }
}

void ContextMenu::render() const {
  if(!this->visible) {
    return;
  }

  for(size_t i = 0; i < this->entries.size(); ++i) {
    const Rectangle& rect = this->rectangles[i];
    Color rect_color = WHITE;
    if(this->hovered_entry && *this->hovered_entry == i) {
      rect_color = Color{100, 100, 255, 255};
    }
    DrawRectangleRec(rect, rect_color);
    DrawText(this->entries[i].c_str(), rect.x + PADDING, rect.y + PADDING, FONT_SIZE, BLACK);
  }
}

void ContextMenu::show(Vector2 position) {
  this->selected_entry = {};
  this->visible = true;
  this->rectangles.clear();
  for(size_t i = 0; i < this->entries.size(); ++i) {
    this->rectangles.emplace_back(position.x,
                                  position.y + i * RECT_HEIGHT,
                                  this->width,
                                  RECT_HEIGHT);
  }
}

std::string ContextMenu::get_entry(size_t index) {
  return this->entries[index];
}

void ContextMenu::set_entry(size_t index, std::string entry) {
  this->entries[index] = entry;
  this->calculate_width();
}

void ContextMenu::calculate_width() {
  this->width = 0;
  for(const std::string& entry: entries) {
    int entry_width = MeasureText(entry.c_str(), FONT_SIZE);
    if(entry_width > this->width) {
      this->width = entry_width;
    }
  }
  this->width += 2 * PADDING;  
}
