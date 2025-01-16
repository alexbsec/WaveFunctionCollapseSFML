#include "include/config.hpp"
#include "include/renderer.hpp"
#include "include/world.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cstdlib>

int main() {
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "wfc");
  std::unique_ptr<World> world = std::make_unique<World>(
      WORLD_X, WORLD_Y);
  Renderer renderer(std::move(world));

  sf::Time wait = sf::seconds(0.0f);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();
    renderer.Update(wait);
    renderer.Draw(window);
    window.display();
  }

  return EXIT_SUCCESS;
}
