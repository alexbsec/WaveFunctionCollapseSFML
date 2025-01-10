#ifndef _WFC_TILES_HPP
#define _WFC_TILES_HPP
#include <SFML/Graphics.hpp>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using string = std::string;
template <typename T, typename P> using umap = std::unordered_map<T, P>;
template <typename T> using uset = std::unordered_set<T>;
template <typename T> using vector = std::vector<T>;

enum Position {
  Top,
  Bottom,
  Left,
  Right,
  TopRight,
  TopLeft,
  BottomRight,
  BottomLeft,
};

enum TileType {
  Wall_TopRightCorner,
  Wall_TopLeftCorner,
  Wall_BottomRightCorner,
  Wall_BottomLeftCorner,
  Wall_Vertical,
  Wall_Horizontal,
  Wall_Void,
  Floor
};

const umap<TileType, string> TEXTURE_PATHS = {
    {Wall_TopRightCorner, "assets/Wall_TopRightCorner.png"},
    {Wall_TopLeftCorner, "assets/Wall_TopLeftCorner.png"},
    {Wall_BottomRightCorner, "assets/Wall_BottomRightCorner.png"},
    {Wall_BottomLeftCorner, "assets/Wall_BottomLeftCorner.png"},
    {Wall_Vertical, "assets/Wall_Vertical.png"},
    {Wall_Horizontal, "assets/Wall_Horizontal"},
    {Floor, "assets/Floor.png"}
};

struct FriendTiles {
  TileType tileType;
  umap<Position, uset<TileType>> tileTypeFriends;

  FriendTiles(const TileType &type, const umap<Position, uset<TileType>> &friends)
    : tileType(type), tileTypeFriends(friends) {}
};

struct Tile {
  int x;
  int y;
  int index;
  TileType type;
  sf::Sprite sprite;
  sf::Texture texture;

  explicit Tile(const TileType &type, int x, int y)
      : x(x), y(y), index(-1), type(type) {
    if (TEXTURE_PATHS.find(type) == TEXTURE_PATHS.end()) {
      throw std::runtime_error("TileError: could not load tile because "
                               "TileType is invalid or it does not exits");
    }

    if (!texture.loadFromFile(TEXTURE_PATHS.at(type))) {
      throw std::runtime_error(
          "TileError: could not load tile. loadFromFile failed");
    }

    sprite.setTexture(texture);
  }
};

uset<TileType> GetFriendTiles(TileType type, Position position);

const vector<FriendTiles*>& GetFriendAllTiles(); 

#endif
