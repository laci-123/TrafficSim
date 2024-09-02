#include "bezier_curve.hpp"


BezierCurve::BezierCurve(Vector2 end_point_1, Vector2 control_point_1, Vector2 control_point_2, Vector2 end_point_2, Color color, float thickness)
  :ep1{end_point_1, 5.0f, color},
   cp1{control_point_1, 5.0f, color},
   cp2{control_point_2, 5.0f, color},
   ep2{end_point_2, 5.0f, color},
   color{color},
   thickness{thickness}
{
  this->ep1.attach(cp1);
  this->ep2.attach(cp2);
}

void BezierCurve::update(float dt) {
  this->ep1.update(dt);
  this->cp1.update(dt);
  this->cp2.update(dt);
  this->ep2.update(dt);
}

void BezierCurve::render() const {
  this->ep1.render();
  this->cp1.render();
  this->cp2.render();
  this->ep2.render();

  DrawSplineSegmentBezierCubic(this->ep1.position,
                               this->cp1.position,
                               this->cp2.position,
                               this->ep2.position,
                               this->thickness,
                               this->color);

  DrawLineEx(this->ep1.position, this->cp1.position, 1, this->color);
  DrawLineEx(this->ep2.position, this->cp2.position, 1, this->color);
}
