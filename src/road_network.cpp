#include "road_network.hpp"


const std::unordered_set<size_t>& RoadNetworkPart::get_neighbours() const {
  return this->neighbours;
}

void RoadNetworkPart::add_neighbour(size_t index) {
  this->neighbours.insert(index);
}

void RoadNetworkPart::remove_neighbour(size_t index) {
  this->neighbours.erase(index);
}

RoadNetwork::RoadNetwork(Assets& assets)
  :assets{assets}
{}

void RoadNetwork::add_part(std::unique_ptr<RoadNetworkPart> part) {
  this->parts.insert({this->index++, std::move(part)});
}

void RoadNetwork::remove_part(size_t index) {
  this->parts.erase(index);
}

void RoadNetwork::update(float dt) {
  for(auto& [index, part]: this->parts){
    part->update(dt);
  }
}

void RoadNetwork::render() const {
  for(const auto& [index, part]: this->parts){
    part->render();
  }
}

Assets& RoadNetwork::get_assets() {
  return this->assets;
}

size_t RoadNetwork::next_index() const {
  return this->index;
}
