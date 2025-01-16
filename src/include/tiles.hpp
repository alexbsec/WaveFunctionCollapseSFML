#ifndef _WFC_TILES_HPP
#define _WFC_TILES_HPP

#include <unordered_set>
#include "config.hpp"

template <typename T> using uset = std::unordered_set<T>;

class Tile {
public:
  Tile(const int &x, const int &y);
  void AddNeighbor(Direction direction, Tile tile);
  Tile GetNeighbor(Direction direction) const;

  int x;
  int y;
  uset<TileType> possibilities;
  size_t entropy;

private:
  umap<Direction, Tile> _neighborTiles;
};

#endif
