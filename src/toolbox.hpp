#ifndef TOOLBOX_INCLUDED_
#define TOOLBOX_INCLUDED_

#include "road_network.hpp"
#include "dragable.hpp"
#include "raylib.h"
#include "raymath.h"
#include <functional>
#include <vector>
#include <memory>
#include <initializer_list>


struct Entry {
  std::string name;
  std::function<std::unique_ptr<RoadNetworkPart>(Vector2, RoadNetwork&)> f;
};

class Toolbox: public Dragable {
public:
  Toolbox(Vector2 position, RoadNetwork& network, std::initializer_list<Entry> entries);
  std::unique_ptr<RoadNetworkPart> update();
  void render() const;
  virtual bool is_mouse_over(Vector2 mouse) const override;
private:
  void calculate_width();
  RoadNetwork& network;
  std::vector<Entry> entries;
  std::optional<size_t> dragged_entry;
  std::vector<Rectangle> rectangles;
  Rectangle back_plate;
  int width;
};

#endif //TOOLBOX_INCLUDED_
