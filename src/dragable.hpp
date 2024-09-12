#ifndef DRAGGABLE_INCLUDED_
#define DRAGGABLE_INCLUDED_

#include "raylib.h"
#include "raymath.h"
#include <functional>

class Dragable {
public:
  Dragable(Vector2 position);
  virtual ~Dragable() = default;
  Vector2 get_position() const;
  void set_position(Vector2 position);
  // Returns how much the object moved since the last update
  Vector2 update(); 
  virtual bool is_mouse_over(Vector2 mouse) const = 0;
private:
  Vector2 position;
  Vector2 old_position;
  std::optional<Vector2> mouse_offset;
  bool mouse_was_already_down;
};

#endif //DRAGGABLE_INCLUDED_
