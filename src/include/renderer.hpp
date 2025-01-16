#ifndef _RENDERER_WFC_HPP
#define _RENDERER_WFC_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "world.hpp"

class Renderer {
public:
  explicit Renderer(World world);
  void Draw(sf::RenderWindow &window);
  void Update();
  World GetWorld() const;

private:
  sf::Sprite _sprite;
  sf::Texture _texture;
  World _world;
};


#endif
