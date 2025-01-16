#include "include/tiles.hpp"
#include "include/config.hpp"
#include <random>
#include <stdexcept>

Tile::Tile(const int &x, const int &y) : x(x), y(y) {
  for (const auto &[key, _] : TILE_RULES) {
    _possibilities.insert(key);
  }

  _entropy = _possibilities.size();
}

void Tile::AddNeighbor(Direction direction, Tile tile) {
  _neighborTiles[direction] = tile;
}

Tile Tile::GetNeighbor(Direction direction) const {
  return _neighborTiles.at(direction);
}

vector<Direction> Tile::GetDirections() const {
  vector<Direction> directions;
  for (const auto &[key, _] : _neighborTiles) {
    directions.push_back(key);
  }

  return directions;
}

uset<TileType> Tile::GetPossibilities() const { return _possibilities; }

size_t Tile::GetEntropy() const { return _entropy; }

void Tile::Collapse() {
  vector<unsigned int> weights;
  for (const TileType &possibility : _possibilities) {
    if (TILE_WEIGHTS.find(possibility) != TILE_WEIGHTS.end()) {
      weights.push_back(TILE_WEIGHTS.at(possibility));
    }
  }

  TileType chosenType = GetRandomChoice(weights);
  _possibilities = uset<TileType>(chosenType);
  _entropy = 0;
}

// Must implement this
bool Tile::Constrain(const uset<TileType> &neighborPossibilities,
                     Direction direction) {
  bool reduced = false;
  return reduced;
}
/* PRIVATE METHODS */

TileType Tile::GetRandomChoice(const vector<unsigned int> &weights) {
  if (_possibilities.size() != weights.size()) {
    throw std::invalid_argument(
        "GetRandomChoice: size of possibilities and weights must be the same");
  }

  umap<TileType, unsigned int> tileWeights;
  auto it = _possibilities.begin();
  for (size_t i = 0; i < tileWeights.size(); i++) {
    tileWeights[*it] = weights[i];
  }

  vector<TileType> tileVec;
  vector<unsigned int> weightVec;

  for (const auto &[tileType, weight] : tileWeights) {
    tileVec.push_back(tileType);
    weightVec.push_back(weight);
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::discrete_distribution<> dist(weightVec.begin(), weightVec.end());

  return tileVec[dist(gen)];
}
