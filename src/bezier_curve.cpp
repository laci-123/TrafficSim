#include "bezier_curve.hpp"


BezierCurve::BezierCurve(Vector2 end_point_1, Vector2 control_point_1, Vector2 control_point_2, Vector2 end_point_2, Color color, float thickness)
  :ep1{end_point_1, 5.0f, color},
   cp1{control_point_1, 5.0f, color},
   cp2{control_point_2, 5.0f, color},
   ep2{end_point_2, 5.0f, color},
   color{color},
   thickness{thickness},
   cached_tight_bounding_rect{this->tight_bounding_rect()}
{
  this->ep1.attach(cp1);
  this->ep2.attach(cp2);
}

Vector2 BezierCurve::derivative_at(float tau) const {
  // BC(tau)  =    (1 - tau)^3*P1 +      3*tau*(1 - tau)^2*C1 +   3tau^2*(1 - tau)*C2 +   tau^3*P2
  // BC'(tau) = -3*(1 - tau)^2*P1 + (9*tau^2 - 12*tau + 3)*C1 + (-9*tau^2 + 6*tau)*C2 + 3*tau^2*P2

  Vector2 v1 = Vector2Scale(this->ep1.position, -3 * (1 - tau) * (1 - tau));
  Vector2 v2 = Vector2Scale(this->cp1.position,  9 * tau * tau - 12 * tau + 3);
  Vector2 v3 = Vector2Scale(this->cp2.position, -9 * tau * tau + 6 * tau);
  Vector2 v4 = Vector2Scale(this->ep2.position,  3 * tau * tau);

  return Vector2Add(v1, Vector2Add(v2, Vector2Add(v3, v4)));
}

Rectangle BezierCurve::tight_bounding_rect() const {
  // The curve touches its tight bounding rectangle
  // where at least one of the coordinates of its derivative is zero
  // or at the end points.
  //
  // BC'(tau) = -3*(1 - tau)^2*P1 + (9*tau^2 - 12*tau + 3)*C1 + (-9*tau^2 + 6*tau)*C2 + 3*tau^2*P2
  // BC'(tau) = (-3*P1 + 9*C1 + -9*C2 + 3*P2)*tau^2 + (6*P1 - 12*C1 + 6*C2)*tau - 3*P1 + 3*C1
  // a := -3*P1 + 9*C1 + -9*C2 + 3*P2
  // b := 6*P1 - 12*C1 + 6*C2
  // c := -3*P1 + 3*C1
  // BC'(tau) = a*tau^2 + b*tau + c
  // BC'.x(tau) = 0 OR BC'.y(tau) = 0
  // a.x*tau^2 + b.x*tau + c.x = 0 OR a.y*tau^2 + b.y*tau + c.y = 0
  
  float ax = -3 * this->ep1.position.x + 9  * this->cp1.position.x - 9 * this->cp2.position.x + 3 * this->ep2.position.x;
  float ay = -3 * this->ep1.position.y + 9  * this->cp1.position.y - 9 * this->cp2.position.y + 3 * this->ep2.position.y;
  float bx =  6 * this->ep1.position.x - 12 * this->cp1.position.x + 6 * this->cp2.position.x;
  float by =  6 * this->ep1.position.y - 12 * this->cp1.position.y + 6 * this->cp2.position.y;
  float cx = -3 * this->ep1.position.x + 3  * this->cp1.position.x;
  float cy = -3 * this->ep1.position.y + 3  * this->cp1.position.y;

  // solving the quadratic equations
  float Dx     = bx*bx - 4*ax*cx;
  float Dy     = by*by - 4*ay*cy;
  float tau_x1 = Dx >= 0 ? (-bx + sqrt(Dx))/(2 * ax) : -1.0;
  float tau_x2 = Dx >= 0 ? (-bx - sqrt(Dx))/(2 * ax) : -1.0;
  float tau_y1 = Dy >= 0 ? (-by + sqrt(Dy))/(2 * ay) : -1.0;
  float tau_y2 = Dy >= 0 ? (-by - sqrt(Dy))/(2 * ay) : -1.0;

  // selecting inner-most points
  float left   = fminf(this->ep1.position.x, this->ep2.position.x);
  float right  = fmaxf(this->ep1.position.x, this->ep2.position.x);;
  float top    = fminf(this->ep1.position.y, this->ep2.position.y);
  float bottom = fmaxf(this->ep1.position.y, this->ep2.position.y);;
  if(0.0 <= tau_x1 && tau_x1 <= 1.0) {
    Vector2 p = GetSplinePointBezierCubic(this->ep1.position, this->cp1.position, this->cp2.position, this->ep2.position, tau_x1);
    if(p.x < left) {
      left = p.x;
    }
    else if(right < p.x) {
      right = p.x;
    }
  }
  if(0.0 <= tau_x2 && tau_x2 <= 1.0) {
    Vector2 p = GetSplinePointBezierCubic(this->ep1.position, this->cp1.position, this->cp2.position, this->ep2.position, tau_x2);
    if(p.x < left) {
      left = p.x;
    }
    else if(right < p.x) {
      right = p.x;
    }
  }
  if(0.0 <= tau_y1 && tau_y1 <= 1.0) {
    Vector2 p = GetSplinePointBezierCubic(this->ep1.position, this->cp1.position, this->cp2.position, this->ep2.position, tau_y1);
    if(p.y < top) {
      top = p.y;
    }
    else if(bottom < p.y) {
      bottom = p.y;
    }
  }
  if(0.0 <= tau_y2 && tau_y2 <= 1.0) {
    Vector2 p = GetSplinePointBezierCubic(this->ep1.position, this->cp1.position, this->cp2.position, this->ep2.position, tau_y2);
    if(p.y < top) {
      top = p.y;
    }
    else if(bottom < p.y) {
      bottom = p.y;
    }
  }

  return Rectangle{left, top, right - left, bottom - top};
}

void BezierCurve::update(float dt) {
  bool ep1_moved = this->ep1.update(dt);
  bool cp1_moved = this->cp1.update(dt);
  bool cp2_moved = this->cp2.update(dt);
  bool ep2_moved = this->ep2.update(dt);

  if(ep1_moved || cp1_moved || cp2_moved || ep2_moved) {
    this->cached_tight_bounding_rect = this->tight_bounding_rect();
  }
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

  DrawRectangleLinesEx(this->cached_tight_bounding_rect, 1.0f, BLUE);
}
