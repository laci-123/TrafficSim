#include "road_network.hpp"


void RoadNetwork::add_part(std::unique_ptr<RoadNetworkPart> part) {
  size_t index = this->parts.size();
  this->parts.push_back(std::move(part));
  this->parts[index]->add_network(this, index);
}

void RoadNetwork::remove_part(size_t index) {
  this->parts[index] = std::move(this->parts.back());
  this->parts.pop_back();
}

void RoadNetwork::update(float dt) {
  for(std::unique_ptr<RoadNetworkPart>& part: this->parts){
    part->update(dt);
  }
}

void RoadNetwork::render() const {
  for(const std::unique_ptr<RoadNetworkPart>& part: this->parts){
    part->render();
  }
}
