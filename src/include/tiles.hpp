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
  vector<Direction> GetDirections() const;
  uset<TileType> GetPossibilities() const;
  size_t GetEntropy() const;
  void Collapse();
  bool Constrain(const uset<TileType> &neighborPossibilities, Direction direction);

  int x;
  int y;

private:
  TileType GetRandomChoice(const vector<unsigned int> &weights);

  size_t _entropy;
  uset<TileType> _possibilities;
  umap<Direction, Tile> _neighborTiles;
};

#endif
