#ifndef ASSETS_INCLUDED_
#define ASSETS_INCLUDED_

#include "raylib.h"
#include <unordered_map>
#include <string>
#include <memory>

struct AssetKey {
  std::string path;
  int width;
  int height;
  bool operator==(const AssetKey& other) const {
    return this->path == other.path && this->width == other.width && this->height == other.height;
  }
};

template <>
struct std::hash<AssetKey> {
  size_t operator()(const AssetKey& key) const {
    return std::hash<std::string>()(key.path) ^ std::hash<int>()(key.width) ^ std::hash<int>()(key.height);
  }
};

class Assets {
public:
  std::shared_ptr<Texture2D> get_texture(const char* path, int width, int height);
private:
  std::unordered_map<AssetKey, std::shared_ptr<Texture2D>> textures;
  void remove_unused_textures();
};

#endif //ASSETS_INCLUDED_
