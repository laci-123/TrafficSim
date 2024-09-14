#ifndef GAME_INCLUDED_
#define GAME_INCLUDED_


#include "road_network.hpp"
#include "toolbox.hpp"
#include "assets.hpp"

class Game {
public:
  Game();
  void update();
  void render() const;
private:
  Assets assets;
  RoadNetwork network;
  Toolbox toolbox;
};

#endif //GAME_INCLUDED_
