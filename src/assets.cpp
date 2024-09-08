#include "assets.hpp"


std::shared_ptr<Texture2D> Assets::get_texture(const char* path, int width, int height) {
  auto key = AssetKey{.path = std::string{path}, .width = width, .height = height};
  if(auto search = this->textures.find(key); search != this->textures.end()) {
    return search->second;
  }
  else {
    Image image = LoadImageSvg(path, width, height);
    Texture texture = LoadTextureFromImage(image);
    UnloadImage(image);
    auto shared_texture{std::make_shared<Texture2D>(texture)};
    this->textures.insert(std::make_pair(key, shared_texture));
    this->remove_unused_textures();
    return shared_texture;
  }
}

void Assets::remove_unused_textures() {
  std::erase_if(this->textures, [](const std::pair<AssetKey, std::shared_ptr<Texture>>& kv) {
    return kv.second.use_count() == 1;
  });
}
