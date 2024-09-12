#include "movable_point.hpp"

MovablePoint::MovablePoint(Vector2 position, float radius, Color color)
  :Dragable{position}, radius{radius}, color{color}
{}

MovablePoint::MovablePoint(const MovablePoint& other)
  :Dragable{other.get_position()},
   radius{other.radius},
   color{other.color},
   attached_points{}
{}

void MovablePoint::attach(MovablePoint& other) {
  this->attached_points.push_back(other);
}
  
Vector2 MovablePoint::update() {
  Vector2 translation{ Dragable::update() };
  for(MovablePoint& point: this->attached_points) {
    point.set_position(Vector2Add(point.get_position(), translation));
  }
  return translation;
}

void MovablePoint::render() const {
  DrawCircleV(this->get_position(), this->radius, this->color);
}

bool MovablePoint::is_mouse_over(Vector2 mouse) const {
  return CheckCollisionPointCircle(mouse, this->get_position(), this->radius);
}
