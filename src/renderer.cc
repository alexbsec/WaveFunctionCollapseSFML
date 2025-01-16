#include "include/renderer.hpp"
#include "include/config.hpp"
#include <stdexcept>

Renderer::Renderer(World world)
  : _world(world) {
  if (!_texture.loadFromFile(SPRITESHEET_PATH)) {
    throw std::runtime_error("Renderer constructor: cannot load spritesheet");
  }

  _sprite.setTexture(_texture);
}

void Renderer::Draw(sf::RenderWindow &window) {
  window.draw(_sprite);
}

void Renderer::Update() {}

World Renderer::GetWorld() const {
  return _world;
}
