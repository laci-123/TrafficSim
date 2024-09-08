#ifndef ROAD_NETWORK_INCLUDED_
#define ROAD_NETWORK_INCLUDED_

#include "raylib.h"
#include "raymath.h"
#include "assets.hpp"
#include <memory>
#include <unordered_map>
#include <unordered_set>

class RoadNetwork;

class RoadNetworkPart {
public:
  virtual ~RoadNetworkPart() {};
  virtual void update(float dt) = 0;
  virtual void render() const = 0;
  const std::unordered_set<size_t>& get_neighbours() const;
  void add_neighbour(size_t index);
  void remove_neighbour(size_t index);
private:
  std::unordered_set<size_t> neighbours;
};

class RoadNetwork {
public:
  RoadNetwork(Assets& assets);
  void add_part(std::unique_ptr<RoadNetworkPart> part);
  void remove_part(size_t index);
  void update(float dt);
  void render() const;
  Assets& get_assets();
  size_t next_index() const;
private:
  std::unordered_map<size_t, std::unique_ptr<RoadNetworkPart>> parts;
  Assets& assets;
  size_t index;
};

#endif //ROAD_NETWORK_INCLUDED_
