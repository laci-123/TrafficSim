#ifndef MOVABLE_POINT_H_
#define MOVABLE_POINT_H_

#include "raylib.h"
#include "raymath.h"


class MovablePoint {
public:
  MovablePoint(Vector2 position);
  void update(float dt);
  void render() const;
private:
  Vector2 position;
};

#endif // MOVABLE_POINT_H_
