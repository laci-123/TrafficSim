#ifndef INTERSECTION_INCLUDED_
#define INTERSECTION_INCLUDED_

#include "road_network.hpp"
#include "dragable.hpp"
#include "raylib.h"
#include "raymath.h"
#include <memory>

class Intersection: public RoadNetworkPart, public Dragable {
public:
  Intersection(Vector2 position, RoadNetwork& network);
  virtual ~Intersection() {};
  virtual void update(float dt) override;
  virtual void render() const override;
  virtual bool is_mouse_over(Vector2 mouse) const override;
private:
  RoadNetwork& network;
  size_t index_in_network;
  std::shared_ptr<Texture2D> tile;
};

#endif //INTERSECTION_INCLUDED_
