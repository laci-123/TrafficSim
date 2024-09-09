#include "assets.hpp"
#include <vector>


std::shared_ptr<Texture2D> Assets::get_texture(const char* path, int width, int height) {
  auto key = AssetKey{.path = std::string{path}, .width = width, .height = height};
  std::shared_ptr<Texture2D> result;

  if(auto search = this->textures.find(key); search != this->textures.end()) {
    result = search->second;
  }
  else {
    Image image = LoadImageSvg(path, width, height);
    Texture texture = LoadTextureFromImage(image);
    UnloadImage(image);
    result = std::shared_ptr<Texture2D>(new Texture2D{texture},
                                        [](Texture2D *texture){
                                          UnloadTexture(*texture);
                                          delete texture;
                                        });
    this->textures.insert(std::make_pair(key, result));
  }

  this->remove_unused_textures();
  return result;
}

void Assets::remove_unused_textures() {
  std::vector<AssetKey> to_be_removed;
  for(auto& [key, value]: this->textures) {
    if(value.use_count() == 1) {
      to_be_removed.push_back(key);
    }
  }
  for(const AssetKey& key: to_be_removed) {
    this->textures.erase(key);
  }
}
