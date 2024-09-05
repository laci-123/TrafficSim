#ifndef ROAD_NETWORK_INCLUDED_
#define ROAD_NETWORK_INCLUDED_

#include "raylib.h"
#include "raymath.h"
#include <memory>
#include <vector>

class RoadNetwork;

class RoadNetworkPart {
public:
  virtual ~RoadNetworkPart() {};
  virtual void update(float dt) = 0;
  virtual void render() const = 0;
  virtual void add_network(RoadNetwork* network, size_t index_in_network) = 0;
};

class RoadNetwork {
public:
  void add_part(std::unique_ptr<RoadNetworkPart> part);
  void remove_part(size_t index);
  void update(float dt);
  void render() const;
private:
  std::vector<std::unique_ptr<RoadNetworkPart>> parts;
};

#endif //ROAD_NETWORK_INCLUDED_
