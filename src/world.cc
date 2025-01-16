#include "include/world.hpp"
#include "include/config.hpp"
#include <chrono>
#include <random>
#include <stack>
#include <string>

World::World(const int &sizeX, const int &sizeY)
    : _sizeX(sizeX), _sizeY(sizeY) {
  // Create the tiles and the grid
  for (int y = 0; y < sizeY; y++) {
    vector<std::shared_ptr<Tile>> tiles;
    for (int x = 0; x < sizeX; x++) {
      std::shared_ptr<Tile> tile = std::make_shared<Tile>(x, y);
      tiles.push_back(std::move(tile));
    }

    _tileRows.push_back(tiles);
  }

  // Add neighbors to the tiles
  for (int y = 0; y < sizeY; y++) {
    for (int x = 0; x < sizeX; x++) {
      std::shared_ptr tile = _tileRows[y][x];
      if (y > 0) {
        tile->AddNeighbor(Direction::Top, _tileRows[y - 1][x]);
      }

      if (y < sizeY - 1) {
        tile->AddNeighbor(Direction::Down, _tileRows[y + 1][x]);
      }

      if (x > 0) {
        tile->AddNeighbor(Direction::Left, _tileRows[y][x - 1]);
      }

      if (x < sizeX - 1) {
        tile->AddNeighbor(Direction::Right, _tileRows[y][x + 1]);
      }
    }
  }
}

vector<vector<std::shared_ptr<Tile>>> World::GetAllTiles() { return _tileRows; }

size_t World::GetEntropy(const int &x, const int &y) const {
  return _tileRows[y][x]->GetEntropy();
}

TileType World::GetTileType(const int &x, const int &y) const {
  return *_tileRows[y][x]->GetPossibilities().begin();
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

vector<std::shared_ptr<Tile>> World::GetAllTilesWithLowestEntropy() const {
  size_t lowestEntropy = TILE_RULES.size();
  vector<std::shared_ptr<Tile>> tiles;

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
  vector<std::shared_ptr<Tile>> lowestEntropyTiles =
      GetAllTilesWithLowestEntropy();

  if (lowestEntropyTiles.empty()) {
    return 0;
  }

  DEBUG("Lowest entropy tiles vector has size: " +
        std::to_string(lowestEntropyTiles.size()));
  auto [x, y] = GetRandomTileToCollapse(lowestEntropyTiles);

  DEBUG("Got tile to collapse at coordinates: (" + std::to_string(x) + ", " +
        std::to_string(y) + ")");

  // Gets the reference for the tile
  std::shared_ptr<Tile> tileToCollapse = _tileRows[y][x];
  tileToCollapse->Collapse();

  DEBUG("Tile collapsed to: " + GetTypeName(GetTileType(x, y)));

  std::stack<std::shared_ptr<Tile>> tileStack;
  tileStack.push(tileToCollapse);
  DEBUG("Starting stack. Stack size: " + std::to_string(tileStack.size()));
  while (!tileStack.empty()) {
    DEBUG("------- STACK PROCESSING --------");
    std::shared_ptr<Tile> tile = tileStack.top();
    DEBUG("Processing tile at: (" + std::to_string(tile->x) + ", " +
          std::to_string(tile->y) + ")");
    tileStack.pop();
    uset<TileType> tilePossibilities = tile->GetPossibilities();
    vector<Direction> directions = tile->GetDirections();
    DEBUG("Number of possibilities for this tile: " +
          std::to_string(tilePossibilities.size()));

    for (const Direction &direction : directions) {
      std::shared_ptr<Tile> neighbor = tile->GetNeighbor(direction);
      DEBUG("Analzing neighbor at: (" + std::to_string(neighbor->x) + ", " +
            std::to_string(neighbor->y) + ")");
      if (neighbor->GetEntropy() != 0) {
        DEBUG("Neighbor at: (" + std::to_string(neighbor->x) + ", " +
              std::to_string(neighbor->y) +
              ") has entropy: " + std::to_string(neighbor->GetEntropy()));
        bool reduced = neighbor->Constrain(tilePossibilities, direction);
        DEBUG("Neighbor got reduced entropy now equals to: " +
              std::to_string(neighbor->GetEntropy()));
        if (reduced) {
          DEBUG("Pushing neihbor at (" + std::to_string(neighbor->x) + ", " + std::to_string(neighbor->y) + ") to stack");
          tileStack.push(neighbor);
        }
      }
    }
  }

  return 1;
}

std::pair<int, int> World::GetRandomTileToCollapse(
    const vector<std::shared_ptr<Tile>> &tiles) const {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 gen(seed);
  std::uniform_int_distribution<int> randomIndex(0, tiles.size());

  int index = randomIndex(gen);
  std::shared_ptr<Tile> selectedTile = tiles[index];
  return std::make_pair(selectedTile->x, selectedTile->y);
}
