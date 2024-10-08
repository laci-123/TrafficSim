#include "road_segment.hpp"


RoadSegment::RoadSegment(Vector2 end_point_1, Vector2 control_point_1, Vector2 control_point_2, Vector2 end_point_2, RoadNetwork& network)
  :bc{end_point_1, control_point_1, control_point_2, end_point_2, WHITE, 1.0f},
   context_menu{"edit", "delete"},
   network{network},
   index_in_network{network.next_index()},
   tile{network.get_assets().get_texture("assets/road_tile.svg", 10, 20)}
{}

RoadSegment::RoadSegment(Vector2 position, RoadNetwork& network)
  :RoadSegment{Vector2Add(position, Vector2{-40, -40}),
               Vector2Add(position, Vector2{0, -40}),
               Vector2Add(position, Vector2{0, 40}),
               Vector2Add(position, Vector2{40, 40}),
               network}
{}

void RoadSegment::update(float dt) {
  if(!this->context_menu.visible){
    Vector2 mouse{GetMousePosition()};
    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && this->bc.check_collision(mouse, 10)) {
        this->context_menu.show(mouse);
    }
  }
  this->context_menu.update(dt);
  if(this->context_menu.selected_entry) {
    size_t selected = *this->context_menu.selected_entry;
    if(this->context_menu.get_entry(selected) == "edit") {
      this->bc.is_in_design_mode = true;
      this->context_menu.set_entry(selected, "done editing");
    }
    else if(this->context_menu.get_entry(selected) == "done editing") {
      this->bc.is_in_design_mode = false;
      this->context_menu.set_entry(selected, "edit");
    }
    if(this->context_menu.get_entry(selected) == "delete") {
      this->network.remove_part(this->index_in_network);
    }
    this->context_menu.selected_entry = {};
  }

  this->bc.update(dt);
}

void RoadSegment::render() const {
  if(this->bc.is_in_design_mode) {
    this->bc.render();
  }
  else {
    for(float tau = 0.0; tau <= 1.0; tau += 0.01) {
        Vector2 p{this->bc.position_at(tau)};
        Vector2 d{this->bc.derivative_at(tau)};
        Vector2 horizontal_right{1, 0};
        float angle{Vector2Angle(d, horizontal_right)};
        Vector2 n{Vector2Rotate(Vector2Normalize(d), 0.5 * M_PI)};
        DrawTextureEx(*this->tile, Vector2Add(p, Vector2Scale(n, -10.0)), angle * -180.0 / M_PI, 1, WHITE);
    }
  }

  this->context_menu.render();
}
