#include "include/tiles.hpp"
#include "include/config.hpp"

Tile::Tile(const int &x, const int &y) 
  : x(x), y(y) {
  for (const auto &[key, _] : TILE_RULES) {
    possibilities.insert(key);
  }

  entropy = possibilities.size();
}

void Tile::AddNeighbor(Direction direction, Tile tile) {
  _neighborTiles[direction] = tile;
}

Tile Tile::GetNeighbor(Direction direction) const {
  return _neighborTiles.at(direction);
}
