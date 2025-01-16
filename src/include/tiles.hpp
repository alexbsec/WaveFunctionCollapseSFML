#ifndef _WFC_TILES_HPP
#define _WFC_TILES_HPP

#include "config.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <unordered_set>

template <typename T> using uset = std::unordered_set<T>;

class Tile {
public:
  Tile(const int &x, const int &y);
  ~Tile() = default;
  void AddNeighbor(Direction direction, std::shared_ptr<Tile> tile);
  std::shared_ptr<Tile> GetNeighbor(Direction direction);
  vector<Direction> GetDirections() const;
  uset<TileType> GetPossibilities() const;
  size_t GetEntropy() const;
  void Collapse();
  bool Constrain(const uset<TileType> &neighborPossibilities,
                 Direction direction);
  sf::Sprite GetSprite() const;

  int x;
  int y;

private:
  TileType GetRandomChoice(const vector<unsigned int> &weights);

  sf::Sprite _sprite;
  sf::Texture _texture;
  size_t _entropy;
  uset<TileType> _possibilities;
  umap<Direction, std::shared_ptr<Tile>> _neighborTiles;
};

#endif
