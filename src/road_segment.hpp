#ifndef ROAD_SEGMENT_HPP_
#define ROAD_SEGMENT_HPP_

#include "bezier_curve.hpp"
#include "context_menu.hpp"
#include "road_network.hpp"
#include "raylib.h"
#include "raymath.h"
#include <memory>

class RoadSegment: public RoadNetworkPart {
public:
  RoadSegment(Vector2 end_point1, Vector2 end_point2, RoadNetwork& network);
  virtual ~RoadSegment() override {};
  virtual void update(float dt) override;
  virtual void render() const override;
private:
  BezierCurve bc;
  ContextMenu context_menu;
  RoadNetwork& network;
  size_t index_in_network;
  std::shared_ptr<Texture2D> tile;
};

#endif // ROAD_SEGMENT_HPP_
