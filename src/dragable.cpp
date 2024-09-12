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

Vector2 Dragable::update() {
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    Vector2 mouse = GetMousePosition();
    if(this->mouse_offset) {
      this->set_position(Vector2Add(mouse, *this->mouse_offset));
    }
    else if (this->is_mouse_over(mouse) && !this->mouse_was_already_down) {
      this->mouse_offset = Vector2Subtract(this->position, mouse);
    }
    else {
      this->mouse_was_already_down = true;
    }
  }
  else {
    this->mouse_offset = {};
    this->mouse_was_already_down = false;
  }

  return Vector2Subtract(this->position, this->old_position);
}
