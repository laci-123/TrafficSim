#include "toolbox.hpp"


static constexpr int FONT_SIZE   = 14;
static constexpr int PADDING     = 4;
static constexpr int RECT_HEIGHT = FONT_SIZE + 2 * PADDING;

Toolbox::Toolbox(Vector2 position, RoadNetwork& network, std::initializer_list<Entry> entries) 
  :position{position}, network{network}, entries{entries}
{
  this->calculate_width();
  for(size_t i = 0; i < this->entries.size(); ++i) {
    this->rectangles.emplace_back(position.x,
                                  position.y + i * RECT_HEIGHT,
                                  this->width,
                                  RECT_HEIGHT);
  }
}

std::unique_ptr<RoadNetworkPart> Toolbox::update() {
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    if(!this->dragged_entry) {
      Vector2 mouse = GetMousePosition();
      for(size_t i = 0; i < this->rectangles.size(); ++i) {
        if(CheckCollisionPointRec(mouse, this->rectangles[i])) {
            this->dragged_entry = i;
        }
      }
    }
    return nullptr;
  }
  else {
    if(this->dragged_entry) {
      Vector2 mouse = GetMousePosition();
      auto result = this->entries[*this->dragged_entry].f(mouse, this->network);
      this->dragged_entry = {};
      return result;
    }
    else {
      return nullptr;
    }
  }
}

void Toolbox::render() const {
  for(size_t i = 0; i < this->entries.size(); ++i) {
    const Rectangle& rect = this->rectangles[i];
    DrawRectangleRec(rect, WHITE);
    DrawText(this->entries[i].name.c_str(), rect.x + PADDING, rect.y + PADDING, FONT_SIZE, BLACK);
  }

  if(this->dragged_entry) {
    Vector2 mouse = GetMousePosition();
    DrawText(this->entries[*this->dragged_entry].name.c_str(), mouse.x, mouse.y, FONT_SIZE, BLACK);
  }
}

void Toolbox::calculate_width() {
  this->width = 0;
  for(const Entry& entry: entries) {
    int entry_width = MeasureText(entry.name.c_str(), FONT_SIZE);
    if(entry_width > this->width) {
      this->width = entry_width;
    }
  }
  this->width += 2 * PADDING;  
}
