#ifndef MOVABLE_POINT_H_
#define MOVABLE_POINT_H_

#include "raylib.h"
#include "raymath.h"
#include <optional>
#include <vector>
#include <functional>


class MovablePoint {
public:
  MovablePoint(Vector2 position, float radius, Color color);
  void attach(MovablePoint& other);
  void update(float dt);
  void render() const;
private:
  Vector2 position;
  float radius;
  Color color;
  std::optional<Vector2> mouse_offset;
  std::vector<std::reference_wrapper<MovablePoint>> attached_points;
};

#endif // MOVABLE_POINT_H_
