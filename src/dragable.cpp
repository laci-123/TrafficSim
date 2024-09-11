#include "dragable.hpp"

Dragable::Dragable(Vector2 position)
  :position{position},
   old_position{position}
{}

Vector2 Dragable::get_position() const {
  return this->position;
}

void Dragable::set_position(Vector2 position) {
  this->old_position = this->position;
  this->position = position;
}

bool Dragable::update() {
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    Vector2 mouse = GetMousePosition();
    if(this->mouse_offset) {
      this->set_position(Vector2Add(mouse, *this->mouse_offset));
    }
    else if (this->is_mouse_over(mouse)) {
      this->mouse_offset = Vector2Subtract(this->position, mouse);
    }
  }
  else {
    this->mouse_offset = {};
  }

  return this->has_moved();
}

bool Dragable::has_moved() const {
  return !Vector2Equals(this->position, this->old_position);
}
