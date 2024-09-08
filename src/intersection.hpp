#ifndef INTERSECTION_INCLUDED_
#define INTERSECTION_INCLUDED_

#include "road_network.hpp"
#include "raylib.h"
#include "raymath.h"
#include <memory>

class Intersection: public RoadNetworkPart {
public:
  Intersection(Vector2 position, RoadNetwork& network);
  virtual ~Intersection() {};
  virtual void update(float dt) override;
  virtual void render() const override;
private:
  Vector2 position;
  RoadNetwork& network;
  size_t index_in_network;
  std::shared_ptr<Texture2D> tile;
};

#endif //INTERSECTION_INCLUDED_
