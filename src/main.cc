#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "include/config.hpp"
#include "include/renderer.hpp"
#include "include/world.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "wfc");
  World world(WINDOW_WIDTH / TILE_SIZE, WINDOW_HEIGHT / TILE_SIZE); 
  Renderer renderer(world);
  
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();
    renderer.Draw(window);
    window.display();
  }

  return EXIT_SUCCESS;
}
