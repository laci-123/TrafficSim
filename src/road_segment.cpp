#include "road_segment.hpp"


RoadSegment::RoadSegment(Vector2 end_point_1, Vector2 end_point_2)
  :bc{end_point_1, Vector2Add(end_point_1, Vector2{10.0f, 10.0f}), Vector2Add(end_point_2, Vector2{-10.0f, -10.0f}), end_point_2, WHITE, 1.0f}
{
  this->is_in_design_mode = true;
  this->bc.is_in_design_mode = true;
}

void RoadSegment::update(float dt) {
  this->bc.update(dt);
}

void RoadSegment::render() const {
  if(this->is_in_design_mode) {
    this->bc.render();
  }

  for(float tau = 0.0; tau <= 1.0; tau += 0.01) {
    Vector2 p{this->bc.position_at(tau)};
    Vector2 d{this->bc.derivative_at(tau)};
    Vector2 n{Vector2Rotate(Vector2Normalize(d), 0.5 * M_PI)};
    Vector2 from{Vector2Add(p, Vector2Scale(n, -10.0))};
    Vector2 to{  Vector2Add(p, Vector2Scale(n,  10.0))};
    DrawLineEx(from, to, 10, GRAY);
  }
}
