#include "road_network.hpp"
#include <iostream>


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
  this->parts.emplace(this->index++, std::move(part));
}

void RoadNetwork::remove_part(size_t index) {
  this->part_to_be_removed = index;
}

void RoadNetwork::update(float dt) {
  if(this->part_to_be_removed) {
    this->parts.erase(*this->part_to_be_removed);
    this->part_to_be_removed = {};
  }
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
