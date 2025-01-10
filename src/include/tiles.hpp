#ifndef _WFC_TILES_HPP
#define _WFC_TILES_HPP
#include <SFML/Graphics.hpp>
#include <memory>
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
  Floor,
  None
};

const umap<TileType, string> TEXTURE_PATHS = {
    {Wall_TopRightCorner, "assets/Wall_TopRightCorner.png"},
    {Wall_TopLeftCorner, "assets/Wall_TopLeftCorner.png"},
    {Wall_BottomRightCorner, "assets/Wall_BottomRightCorner.png"},
    {Wall_BottomLeftCorner, "assets/Wall_BottomLeftCorner.png"},
    {Wall_Vertical, "assets/Wall_Vertical.png"},
    {Wall_Horizontal, "assets/Wall_Horizontal.png"},
    {Wall_Void, "assets/Wall_Void.png"},
    {Floor, "assets/Floor.png"}};

const umap<Position, uset<TileType>> WTRCFriends = {
    {Top, {Floor, Wall_Void}},
    {Bottom, {Wall_Vertical}},
    {Left, {Wall_Horizontal}},
    {Right, {Floor, Wall_Void}},
    {TopRight, {Floor, Wall_Void, Wall_BottomLeftCorner}},
    {TopLeft, {Floor, Wall_Void}},
    {BottomRight, {Floor, Wall_Void}},
    {BottomLeft, {Floor}},
};

const umap<Position, uset<TileType>> WTLCFriends = {
    {Top, {Floor, Wall_Void}},
    {Bottom, {Wall_Vertical}},
    {Left, {Floor, Wall_Void}},
    {Right, {Wall_Horizontal}},
    {TopRight, {Floor, Wall_Void}},
    {TopLeft, {Floor, Wall_Void, Wall_BottomRightCorner}},
    {BottomRight, {Floor}},
    {BottomLeft, {Floor, Wall_Void}},
};

const umap<Position, uset<TileType>> WBRCFriends = {
    {Top, {Wall_Vertical}},
    {Bottom, {Floor, Wall_Void}},
    {Left, {Wall_Horizontal}},
    {Right, {Floor, Wall_Void}},
    {TopRight, {Floor, Wall_Void}},
    {TopLeft, {Floor}},
    {BottomRight, {Floor, Wall_Void, Wall_TopLeftCorner}},
    {BottomLeft, {Floor, Wall_Void}},
};

const umap<Position, uset<TileType>> WBLCFriends = {
    {Top, {Wall_Vertical}},
    {Bottom, {Floor, Wall_Void}},
    {Left, {Floor, Wall_Void}},
    {Right, {Wall_Horizontal}},
    {TopRight, {Floor}},
    {TopLeft, {Floor, Wall_Void}},
    {BottomRight, {Floor, Wall_Void}},
    {BottomLeft, {Floor, Wall_Void, Wall_TopRightCorner}},
};

const umap<Position, uset<TileType>> WVFriends = {
    {Top, {Wall_Vertical, Wall_TopRightCorner, Wall_TopLeftCorner}},
    {Bottom, {Wall_Vertical, Wall_BottomRightCorner, Wall_BottomLeftCorner}},
    {Left, {Floor, Wall_Void}},
    {Right, {Floor, Wall_Void}},
    {TopRight, {Floor, Wall_Void, Wall_Horizontal}},
    {TopLeft, {Floor, Wall_Void, Wall_Horizontal}},
    {BottomRight, {Floor, Wall_Void, Wall_Horizontal}},
    {BottomLeft, {Floor, Wall_Void, Wall_Horizontal}},
};

const umap<Position, uset<TileType>> WHFriends = {
    {Top, {Floor, Wall_Void}},
    {Bottom, {Floor, Wall_Void}},
    {Left, {Wall_Horizontal, Wall_TopLeftCorner, Wall_BottomLeftCorner}},
    {Right, {Wall_Horizontal, Wall_TopRightCorner, Wall_BottomRightCorner}},
    {TopRight, {Floor, Wall_Void, Wall_Vertical}},
    {TopLeft, {Floor, Wall_Void, Wall_Vertical}},
    {BottomRight, {Floor, Wall_Void, Wall_Vertical}},
    {BottomLeft, {Floor, Wall_Void, Wall_Vertical}},
};

const umap<Position, uset<TileType>> VOIDFriends = {
    {Top,
     {Wall_Void, Wall_BottomRightCorner, Wall_BottomLeftCorner,
      Wall_Horizontal}},
    {Bottom,
     {Wall_Void, Wall_TopRightCorner, Wall_TopLeftCorner, Wall_Horizontal}},
    {Left,
     {Wall_Void, Wall_TopRightCorner, Wall_BottomRightCorner, Wall_Vertical}},
    {Right,
     {Wall_Void, Wall_TopLeftCorner, Wall_BottomLeftCorner, Wall_Vertical}},
    {TopRight,
     {Wall_Void, Wall_TopLeftCorner, Wall_BottomLeftCorner,
      Wall_BottomRightCorner, Wall_Vertical, Wall_Horizontal}},
    {TopLeft,
     {Wall_Void, Wall_TopRightCorner, Wall_BottomLeftCorner,
      Wall_BottomRightCorner, Wall_Vertical, Wall_Horizontal}},
    {BottomRight,
     {Wall_Void, Wall_TopLeftCorner, Wall_TopRightCorner, Wall_BottomLeftCorner,
      Wall_Vertical, Wall_Horizontal}},
    {BottomLeft,
     {Wall_Void, Wall_TopLeftCorner, Wall_TopRightCorner,
      Wall_BottomRightCorner, Wall_Vertical, Wall_Horizontal}},
};

const umap<Position, uset<TileType>> FLOORFriends = {
    {Top, {Floor, Wall_Horizontal}},
    {Bottom, {Floor, Wall_Horizontal}},
    {Left, {Floor, Wall_Vertical}},
    {Right, {Floor, Wall_Vertical}},
    {TopRight, {Floor, Wall_TopRightCorner}},
    {TopLeft, {Floor, Wall_TopLeftCorner}},
    {BottomRight, {Floor, Wall_BottomRightCorner}},
    {BottomLeft, {Floor, Wall_BottomLeftCorner}},
};

struct FriendTiles {
  TileType tileType;
  umap<Position, uset<TileType>> tileTypeFriends;

  FriendTiles(const TileType &type,
              const umap<Position, uset<TileType>> &friends)
      : tileType(type), tileTypeFriends(friends) {}
};

struct Tile {
  int x;
  int y;
  TileType type;
  sf::Sprite sprite;
  sf::Texture texture;

  Tile(const TileType &type, int x, int y) : x(x), y(y), type(type) {
    if (type == TileType::None)
      return;

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

  void SetPosition(float x, float y) { sprite.setPosition(x, y); }
};

struct GridCell {
  int index;
  bool collapsed;
  std::unique_ptr<Tile> tile;
  uset<TileType> states;

  GridCell() : index(-1), collapsed(false), tile(nullptr) {
    states = {Wall_BottomLeftCorner,
              Wall_BottomRightCorner,
              Wall_TopLeftCorner,
              Wall_TopRightCorner,
              Wall_Vertical,
              Wall_Horizontal,
              Wall_Void,
              Floor};
  }

  bool operator==(const GridCell &other) const {
    return states == other.states && collapsed == other.collapsed;
  }

  void SetTile(std::unique_ptr<Tile> tile) { this->tile = std::move(tile); }
};

#endif
