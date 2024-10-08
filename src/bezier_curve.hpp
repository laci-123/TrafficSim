#ifndef BEZIER_CURVE_H_
#define BEZIER_CURVE_H_

#include "movable_point.hpp"
#include "raylib.h"
#include "raymath.h"

class BezierCurve {
public:
  BezierCurve(Vector2 end_point_1, Vector2 control_point_1, Vector2 control_point_2, Vector2 end_point_2, Color color, float thickness);
  BezierCurve(const BezierCurve& other);
  Vector2 position_at(float tau) const;
  Vector2 derivative_at(float tau) const;
  void update(float dt);
  void render() const;
  bool is_in_design_mode;
  bool check_collision(Vector2 c, float r);
private:
  Rectangle tight_bounding_rect() const;
  bool is_mouse_over;
  MovablePoint ep1; 
  MovablePoint cp1; 
  MovablePoint cp2; 
  MovablePoint ep2; 
  MovablePoint mp;
  Color color;
  float thickness;
  Rectangle cached_tight_bounding_rect;
};

#endif // BEZIER_CURVE_H_
