#include "movable_point.hpp"

MovablePoint::MovablePoint(Vector2 position, float radius, Color color)
  :position{position}, radius{radius}, color{color}
{}
  
void MovablePoint::update(float dt) {
  if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    this->mouse_offset = {};
    return;
  }
  
  Vector2 mouse = GetMousePosition();
  if(this->mouse_offset) {
    this->position = Vector2Add(mouse, *this->mouse_offset);
  }
  else if (CheckCollisionPointCircle(mouse, this->position, this->radius)) {
    this->mouse_offset = Vector2Subtract(this->position, mouse);
  }
}

void MovablePoint::render() const {
  DrawCircleV(this->position, this->radius, this->color);
}
