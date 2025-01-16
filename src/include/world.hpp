#ifndef _WORLD_WFC_HPP
#define _WORLD_WFC_HPP

#include <vector>
#include "tiles.hpp"

template <typename T> using vector = std::vector<T>;

class World {
public:
  World(const int& sizeX, const int& sizeY);
  size_t GetEntropy(const int &x, const int &y) const;
  TileType GetTileType(const int &x, const int &y) const;
  size_t GetLowestEntropy() const;
  vector<Tile> GetAllTilesWithLowestEntropy() const;
  int WaveFunctionCollapse();

private:
  std::pair<int, int> GetRandomTileToCollapse(const vector<Tile> &tiles) const;
  int _sizeX;
  int _sizeY;
  vector<vector<Tile>> _tileRows;

};

#endif
