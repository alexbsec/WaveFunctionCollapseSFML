#include "include/renderer.hpp"
#include "include/config.hpp"
#include <SFML/System/Sleep.hpp>
#include <algorithm>

Renderer::Renderer(std::unique_ptr<World> world) : _world(std::move(world)) {
  _allRendered = false;
}

void Renderer::Update(sf::Time deltaTime) {
  int got = _world->WaveFunctionCollapse(); 
}

void Renderer::Draw(sf::RenderWindow &window) {
  vector<vector<std::shared_ptr<Tile>>> tiles = _world->GetAllTiles();
  size_t sizeY = tiles.size();
  size_t sizeX = tiles[0].size();
  for (size_t y = 0; y < sizeY; y++) {
    for (size_t x = 0; x < sizeX; x++) {
      if (tiles[y][x]->GetSprite().getTexture() == nullptr)
        continue;

      window.draw(tiles[y][x]->GetSprite());
    }
  }
}


bool Renderer::IsAllRendered() {
  vector<vector<std::shared_ptr<Tile>>> tiles = _world->GetAllTiles();
  return std::all_of(tiles.begin(), tiles.end(),
                     [](const vector<std::shared_ptr<Tile>> &inner) {
                       return std::all_of(
                           inner.begin(), inner.end(),
                           [](const std::shared_ptr<Tile> &tile) {
                             return tile->GetEntropy() == 0;
                           });
                     });
}
