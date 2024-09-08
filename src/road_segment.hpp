#ifndef ROAD_SEGMENT_HPP_
#define ROAD_SEGMENT_HPP_

#include "bezier_curve.hpp"
#include "context_menu.hpp"
#include "road_network.hpp"
#include "assets.hpp"
#include "raylib.h"
#include "raymath.h"
#include <memory>

class RoadSegment: public RoadNetworkPart {
public:
  RoadSegment(Vector2 end_point1, Vector2 end_point2, Assets& assets);
  virtual ~RoadSegment() override {};
  virtual void update(float dt) override;
  virtual void render() const override;
  virtual void add_network(RoadNetwork* network, size_t index_in_network) override;
private:
  BezierCurve bc;
  std::shared_ptr<Texture2D> tile;
  ContextMenu context_menu;
  RoadNetwork* network;
  size_t index_in_network;
};

#endif // ROAD_SEGMENT_HPP_
