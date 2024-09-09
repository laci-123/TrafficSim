#include "assets.hpp"
#include <vector>


std::shared_ptr<Texture2D> Assets::get_texture(const char* path, int width, int height) {
  auto key = AssetKey{.path = std::string{path}, .width = width, .height = height};
  if(auto search = this->textures.find(key); search != this->textures.end()) {
    this->remove_unused_textures();
    return search->second;
  }
  else {
    Image image = LoadImageSvg(path, width, height);
    Texture texture = LoadTextureFromImage(image);
    UnloadImage(image);
    auto shared_texture{std::shared_ptr<Texture2D>(new Texture2D{texture},
                                                   [](Texture2D *texture){
                                                     UnloadTexture(*texture);
                                                     delete texture;
                                                   })};
    this->textures.insert(std::make_pair(key, shared_texture));
    this->remove_unused_textures();
    return shared_texture;
  }
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
