#include "include/tiles.hpp"
#include "include/config.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <array>
#include <random>
#include <stdexcept>

Tile::Tile(const int &x, const int &y) : x(x), y(y) {
  for (const auto &[key, _] : TILE_RULES) {
    _possibilities.insert(key);
  }

  _entropy = _possibilities.size();
}

void Tile::AddNeighbor(Direction direction, std::shared_ptr<Tile> tile) {
  _neighborTiles.emplace(direction, tile);
}

std::shared_ptr<Tile> Tile::GetNeighbor(Direction direction) {
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
  _possibilities = {chosenType};
  _entropy = 0;
  std::array<int, 2> coordinates = TILE_SPRITESHEET_POSITION.at(chosenType);
  _texture.loadFromFile(
      SPRITESHEET_PATH,
      sf::IntRect(coordinates[0], coordinates[1], TILE_SIZE, TILE_SIZE));
  _sprite.setTexture(_texture);
  _sprite.setPosition(x, y);
}

// Must implement this
bool Tile::Constrain(const uset<TileType> &neighborPossibilities,
                     Direction direction) {
  if (_entropy == 0)
    return false;

  bool reduced = false;

  uset<TileType> connectors;
  for (const TileType &neighborPossibility : neighborPossibilities) {
    connectors.insert(TILE_RULES.at(neighborPossibility).at(direction));
  }

  Direction opposite;
  switch (direction) {
  case Direction::Top:
    opposite = Direction::Down;
    break;
  case Direction::Down:
    opposite = Direction::Top;
    break;
  case Direction::Left:
    opposite = Direction::Right;
    break;
  case Direction::Right:
    opposite = Direction::Left;
    break;
  }

  const uset<TileType> possibilitiesCopy = _possibilities;
  for (const TileType &possibility : possibilitiesCopy) {
    TileType oppositeTile = TILE_RULES.at(possibility).at(opposite);
    if (connectors.find(oppositeTile) == connectors.end()) {
      DEBUG("[DISCARDED] Possibility " + GetTypeName(possibility) +
            " discarded for OPPOSITE direction " + GetDirectionName(opposite));
      _possibilities.erase(possibility);
      reduced = true;
    } else {
      DEBUG("[CONSIDERED] Found valid possibility " + GetTypeName(possibility) +
            " at OPPOSITE direction " + GetDirectionName(opposite));
    }
  }

  _entropy = _possibilities.size();

  return reduced;
}

sf::Sprite Tile::GetSprite() const { return _sprite; }

/* PRIVATE METHODS */

TileType Tile::GetRandomChoice(const std::vector<unsigned int> &weights) {
  // Validate input sizes
  if (_possibilities.size() != weights.size()) {
    throw std::invalid_argument(
        "GetRandomChoice: size of possibilities and weights must be the same");
  }

  // Use std::discrete_distribution to pick one element directly
  std::random_device rd;
  std::mt19937 gen(rd());
  std::discrete_distribution<> dist(weights.begin(), weights.end());

  auto it = _possibilities.begin();
  std::advance(it, dist(gen)); // Move iterator to the chosen index
  return *it;
}
