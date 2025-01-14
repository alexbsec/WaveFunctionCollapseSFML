#ifndef _WFC_TILES_HPP
#define _WFC_TILES_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <random>
#include <set>
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
  Null,
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

const umap<TileType, umap<Position, uset<TileType>>> TileTypeToFriends = {
    {Wall_TopRightCorner, WTRCFriends},
    {Wall_TopLeftCorner, WTLCFriends},
    {Wall_BottomRightCorner, WBRCFriends},
    {Wall_BottomLeftCorner, WBLCFriends},
    {Wall_Horizontal, WHFriends},
    {Wall_Vertical, WVFriends},
    {Wall_Void, VOIDFriends},
    {Floor, FLOORFriends},
};

struct States {
  umap<TileType, double> weights;
  TileType collapsedState = TileType::None;

  States() {
    weights = {{Wall_TopRightCorner, 1.0},
               {Wall_TopLeftCorner, 1.0},
               {Wall_BottomLeftCorner, 1.0},
               {Wall_BottomRightCorner, 1.0},
               {Wall_Horizontal, 1.0},
               {Wall_Vertical, 1.0},
               {Wall_Void, 1.0},
               {Floor, 1.0}};

    Normalize();
  }

  void Initialize() {
    weights = {{Wall_TopRightCorner, 1.0},
               {Wall_TopLeftCorner, 1.0},
               {Wall_BottomLeftCorner, 1.0},
               {Wall_BottomRightCorner, 1.0},
               {Wall_Horizontal, 1.0},
               {Wall_Vertical, 1.0},
               {Wall_Void, 1.0},
               {Floor, 1.0}};

    Normalize();

  }

  void Normalize() {
    double totalWeight = 0.0;
    for (const auto &[_, w] : weights) {
      totalWeight += w;
    }

    for (auto &[_, w] : weights) {
      w = w / totalWeight;
    }
  }

  umap<TileType, double> Get() const {
    return weights;
  }

  void Insert(TileType type, double weight) {
    weights[type] = weight;
  }

  void UpdateWeight(TileType type, double weight) {
    if (weights.find(type) != weights.end()) {
      // update
      weights[type] = weight;
      Normalize();
    }
  }

  void RemoveState(TileType type) {
    weights.erase(type);
    if (!Empty()) Normalize();
  }

  double GetWeight(TileType type) const {
    if (weights.find(type) != weights.end()) {
      return weights.at(type);
    }

    return 0.0;
  }

  size_t Size() { return weights.size(); }

  size_t Size() const { return weights.size(); }

  bool Empty() { return weights.empty(); }

  bool HasState(TileType type) const {
    return weights.find(type) != weights.end();
  }

  bool operator==(const States &other) const {
    return weights == other.weights;
  }

  TileType Pick() {
    if (Empty()) 
      throw std::runtime_error("Cannot pick a state in empty state object");

    if (Size() == 1) {
      auto it = weights.begin();
      return it->first;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    double random = dist(gen);
    double cumulativeWeihgt = 0.0;

    for (const auto &[type, w] : weights) {
      cumulativeWeihgt += w;
      if (random < cumulativeWeihgt) {
        return type;
      }
    }

    // Should never reach here if weights are normalized
    throw std::runtime_error("PickRandom: could not pick a tile type randomly. "
                             "Weights possibly non normalized");
  }
 
  void Collapse() {
    TileType type = Pick();
    Collapse(type);
  }

  // Never use this explicitly, only for debugging purposes
  void Collapse(TileType type) {
    if (weights.find(type) == weights.end()) {
      throw std::runtime_error("Collapse: cannot collapse to given state because "
                               "State object does not contain it");
    } else {
      auto pair = weights.find(type);
      weights.clear();
      weights[pair->first] = pair->second;
      Normalize();
    }

    collapsedState = type;
  }
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
  States states;

  GridCell() : index(-1), collapsed(false), tile(nullptr) {}

  bool operator==(const GridCell &other) const {
    return states == other.states && collapsed == other.collapsed;
  }

  void SetTile(std::unique_ptr<Tile> tile) { this->tile = std::move(tile); }
};

#endif
