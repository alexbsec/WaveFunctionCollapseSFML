#ifndef _WORLD_WFC_HPP
#define _WORLD_WFC_HPP

#include <vector>
#include "tiles.hpp"

template <typename T> using vector = std::vector<T>;

class World {
public:
  World(const int& sizeX, const int& sizeY);
  
private:
  int _sizeX;
  int _sizeY;
  vector<vector<Tile>> _tileRows;

};

#endif
