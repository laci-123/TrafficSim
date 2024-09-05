#ifndef ROAD_SEGMENT_HPP_
#define ROAD_SEGMENT_HPP_

#include "bezier_curve.hpp"
#include "context_menu.hpp"
#include "raylib.h"
#include "raymath.h"

class RoadSegment {
public:
  RoadSegment(Vector2 end_point1, Vector2 end_point2);
  ~RoadSegment();
  void update(float dt);
  void render() const;
private:
  BezierCurve bc;
  Texture2D tile;
  ContextMenu context_menu;
};

#endif // ROAD_SEGMENT_HPP_
