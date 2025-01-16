#include "include/world.hpp"
#include <chrono>
#include <random>
#include <stack>

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
        tile.AddNeighbor(Direction::Top, _tileRows[y - 1][x]);
      }

      if (y < sizeY - 1) {
        tile.AddNeighbor(Direction::Down, _tileRows[y + 1][x]);
      }

      if (x > 0) {
        tile.AddNeighbor(Direction::Left, _tileRows[y][x - 1]);
      }

      if (x < sizeX - 1) {
        tile.AddNeighbor(Direction::Right, _tileRows[y][x + 1]);
      }
    }
  }
}

size_t World::GetEntropy(const int &x, const int &y) const {
  return _tileRows[y][x].GetEntropy();
}

TileType World::GetTileType(const int &x, const int &y) const {
  return *_tileRows[y][x].GetPossibilities().begin();
}

size_t World::GetLowestEntropy() const {
  size_t lowestEntropy = TILE_RULES.size();
  for (int y = 0; y < _sizeY; y++) {
    for (int x = 0; x < _sizeX; x++) {
      size_t currEntropy = GetEntropy(x, y);
      if (currEntropy > 0 && currEntropy < lowestEntropy) {
        lowestEntropy = currEntropy;
      }
    }
  }

  return lowestEntropy;
}

vector<Tile> World::GetAllTilesWithLowestEntropy() const {
  size_t lowestEntropy = TILE_RULES.size();
  vector<Tile> tiles;

  for (int y = 0; y < _sizeY; y++) {
    for (int x = 0; x < _sizeX; x++) {
      size_t currEntropy = GetEntropy(x, y);
      if (currEntropy == 0)
        continue;

      if (currEntropy < lowestEntropy) {
        tiles.clear();
        lowestEntropy = currEntropy;
      }

      if (currEntropy == lowestEntropy) {
        tiles.push_back(_tileRows[y][x]);
      }
    }
  }

  return tiles;
}

int World::WaveFunctionCollapse() {
  vector<Tile> lowestEntropyTiles = GetAllTilesWithLowestEntropy();

  if (lowestEntropyTiles.empty())
    return 0;

  auto [x, y] =
      GetRandomTileToCollapse(lowestEntropyTiles);

  // Gets the reference for the tile
  Tile &tileToCollapse = _tileRows[y][x]; 
  tileToCollapse.Collapse();

  std::stack<Tile> tileStack; 
  tileStack.push(tileToCollapse);
  while (!tileStack.empty()) {
    Tile &tile = tileStack.top();
    tileStack.pop();
    uset<TileType> tilePossibilities = tile.GetPossibilities();
    vector<Direction> directions = tile.GetDirections();

    for (const Direction &direction : directions) {
      Tile &neighbor = tile.GetNeighbor(direction);
      if (neighbor.GetEntropy() != 0) {
        bool reduced = neighbor.Constrain(tilePossibilities, direction); 

        if (reduced) {
          tileStack.push(neighbor);
        }
      }
    }
  }

  return 1;
}

std::pair<int, int>
World::GetRandomTileToCollapse(const vector<Tile> &tiles) const {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 gen(seed);
  std::uniform_int_distribution<int> randomIndex(0, tiles.size());

  int index = randomIndex(gen);
  Tile selectedTile = tiles[index];
  return std::make_pair(selectedTile.x, selectedTile.y);
}
