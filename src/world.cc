#include "include/world.hpp"

World::World(const int &sizeX, const int &sizeY)
    : _sizeX(sizeX), _sizeY(sizeY) {
  // Create the tiles and the grid
  for (int y = 0; y < sizeY; y++) {
    vector<Tile> tiles;
    for (int x = 0; x < sizeX; x++) {
      Tile tile(x, y);
      tiles.push_back(tile);
    }

    _tileRows.push_back(tiles);
  }

  // Add neighbors to the tiles
  for (int y = 0; y < sizeY; y++) {
    for (int x = 0; x < sizeX; x++) {
      Tile tile = _tileRows[y][x];
      if (y > 0) {
        tile.AddNeighbor(Position::Top, _tileRows[y - 1][x]);
      }

      if (y < sizeY - 1) {
        tile.AddNeighbor(Position::Down, _tileRows[y + 1][x]);
      }

      if (x > 0) {
        tile.AddNeighbor(Position::Left, _tileRows[y][x - 1]);
      }

      if (x < sizeX - 1) {
        tile.AddNeighbor(Position::Right, _tileRows[y][x + 1]);
      }
    }
  }
}
