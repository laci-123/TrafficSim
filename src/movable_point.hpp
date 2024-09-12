#ifndef MOVABLE_POINT_H_
#define MOVABLE_POINT_H_

#include "raylib.h"
#include "raymath.h"
#include "dragable.hpp"
#include <vector>
#include <functional>


class MovablePoint: public Dragable {
public:
  MovablePoint(Vector2 position, float radius, Color color);
  MovablePoint(const MovablePoint& other);
  virtual bool is_mouse_over(Vector2 mouse) const override;
  void attach(MovablePoint& other);
  // Returns how much the object moved since the last update
  Vector2 update();
  void render() const;
  float radius;
  Color color;
private:
  std::vector<std::reference_wrapper<MovablePoint>> attached_points;
};

#endif // MOVABLE_POINT_H_
