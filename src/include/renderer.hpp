#ifndef _RENDERER_WFC_HPP
#define _RENDERER_WFC_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "world.hpp"

class Renderer {
public:
  explicit Renderer(std::unique_ptr<World> world);
  void Draw(sf::RenderWindow &window);
  void Update(sf::Time deltaTime);

private:
  bool IsAllRendered();
  umap<TileType, sf::Sprite> _sprites;
  sf::Texture _texture;
  std::unique_ptr<World> _world;
  bool _allRendered;
};


#endif
