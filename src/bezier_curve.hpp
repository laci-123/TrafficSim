#ifndef BEZIER_CURVE_H_
#define BEZIER_CURVE_H_

#include "movable_point.hpp"
#include "raylib.h"
#include "raymath.h"

class BezierCurve {
public:
  BezierCurve(Vector2 end_point_1, Vector2 control_point_1, Vector2 control_point_2, Vector2 end_point_2, Color color, float thickness);
  Vector2 derivative_at(float tau) const;
  void update(float dt);
  void render() const;
private:
  Rectangle tight_bounding_rect() const;
  MovablePoint ep1; 
  MovablePoint cp1; 
  MovablePoint cp2; 
  MovablePoint ep2; 
  Color color;
  float thickness;
  Rectangle cached_tight_bounding_rect;
};

#endif // BEZIER_CURVE_H_
