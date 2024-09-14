#include "toolbox.hpp"


static constexpr int FONT_SIZE     = 14;
static constexpr int PADDING       = 4;
static constexpr int RECT_HEIGHT   = FONT_SIZE + 2 * PADDING;
static constexpr int MARGIN        = 5;
static constexpr int HEADER_HEIGHT = FONT_SIZE + PADDING + MARGIN;

Toolbox::Toolbox(Vector2 position, RoadNetwork& network, std::initializer_list<Entry> entries) 
  :Dragable{position}, network{network}, entries{entries}
{
  this->calculate_width();
  for(size_t i = 0; i < this->entries.size(); ++i) {
    this->rectangles.push_back(Rectangle{position.x,
                                         position.y + i * RECT_HEIGHT,
                                         static_cast<float>(this->width),
                                         RECT_HEIGHT});
  }
  this->back_plate = Rectangle{
    .x      = position.x - MARGIN,
    .y      = position.y - HEADER_HEIGHT,
    .width  = static_cast<float>(this->width + 2 * MARGIN),
    .height = static_cast<float>(this->entries.size() * RECT_HEIGHT + HEADER_HEIGHT + MARGIN)
  };
}

bool Toolbox::is_mouse_over(Vector2 mouse) const {
  return CheckCollisionPointRec(mouse, this->back_plate);
}

std::unique_ptr<RoadNetworkPart> Toolbox::update() {
  Vector2 tr{ Dragable::update() };
  if(!Vector2Equals(tr, Vector2{0, 0})) {
    for(size_t i = 0; i < this->entries.size(); ++i) {
      this->rectangles[i] = Rectangle{
        .x      = this->get_position().x,
        .y      = this->get_position().y + i * RECT_HEIGHT,
        .width  = static_cast<float>(this->width),
        .height = RECT_HEIGHT
      };
    }
    this->back_plate = Rectangle{
      .x      = this->get_position().x - MARGIN,
      .y      = this->get_position().y - HEADER_HEIGHT,
      .width  = static_cast<float>(this->width + 2 * MARGIN),
      .height = static_cast<float>(this->entries.size() * RECT_HEIGHT + HEADER_HEIGHT + MARGIN)
    };
  }
  
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
  DrawRectangleRounded(this->back_plate, 0.2, 10, Color{.r = 0, .g = 200, .b = 0, .a = 255});
  DrawText("Toolbox", this->back_plate.x + MARGIN, back_plate.y + MARGIN, FONT_SIZE, BLACK);

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
