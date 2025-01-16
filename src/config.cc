#include "include/config.hpp"

string GetTypeName(TileType type) {
  return TILE_NAMES.at(type);
}

string GetDirectionName(Direction dir) {
  return DIR_NAMES.at(dir);
}
