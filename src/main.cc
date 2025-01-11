#include "include/tiles.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>
#include <stdexcept>

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

const int PIXEL_SIZE = 16;

const int UNITS = 32;
const float SCALE_X = (float)WINDOW_WIDTH / (UNITS * PIXEL_SIZE);
const float SCALE_Y = (float)WINDOW_HEIGHT / (UNITS * PIXEL_SIZE);
const float SCALE = std::min(SCALE_X, SCALE_Y);

template <typename Iterator>
Iterator RandomElement(Iterator begin, Iterator end) {
  const unsigned long n = std::distance(begin, end);
  const unsigned long divisor = ((long)RAND_MAX + 1) / n;

  unsigned long k;
  do {
    k = rand() / divisor;
  } while (k >= n);

  std::advance(begin, k);
  return begin;
}

void HandleGrid(vector<GridCell> &grid) {
  vector<size_t> indices(grid.size());
  std::iota(indices.begin(), indices.end(), 0);

  // Sort so that we know which grid cell has least amount of possible
  // states to be in
  std::sort(indices.begin(), indices.end(), [&grid](size_t a, size_t b) {
    return grid[a].states.size() < grid[b].states.size();
  });

  // Since its sorted, we can get a minimum number of states
  // at index 0
  size_t len = grid[indices[0]].states.size();

  std::cout << len << std::endl;

  // Find the index where the number of states exceeds the minimum
  // in the case where we have more than one cell with the minimum len
  auto it =
      std::find_if(indices.begin(), indices.end(), [&grid, len](size_t idx) {
        return grid[idx].states.size() > len;
      });

  // Determine the stopping index (number of cells with minimum states)
  // this can be 0
  size_t stopIndex = std::distance(indices.begin(), it);
  int random = rand() % (stopIndex);

  // Pick a random index that is within range [0, stopIndex - 1]
  // and grab that cell on the grid
  size_t randomPick = indices[random];
  GridCell &cell = grid[randomPick];

  // Check if the possible states of this cell is only one
  // and if so, mark it as collapsed
  if (cell.states.size() == 1) {
    cell.collapsed = true;
  } else {
    // If there is more than one possible state, it means we need to randomly
    // pick a state and collapse the cell to it
    auto pick = RandomElement(cell.states.begin(), cell.states.end());
    cell.states = uset<TileType>{*pick};
    cell.collapsed = true;
  }
}

bool IsFriend(TileType type, Position position, const GridCell &adjCell) {
  // Checks if the adjacent cell tile is empty
  // in this case we know that the type is a friend type
  // independetly of the position
  if (adjCell.tile == nullptr)
    return true;

  // From here on, we know for sure the adjacent cell is collapsed
  // and have its own friends
  TileType adjType = adjCell.tile->type;

  auto it1 = TileTypeToFriends.find(adjType);
  if (it1 == TileTypeToFriends.end()) {
    // This should never throw
    throw std::runtime_error(
        "IsFriend: could not find friends for this tile type");
  }

  const umap<Position, uset<TileType>> &friendsMap = it1->second;
  auto it2 = friendsMap.find(position);
  if (it2 == friendsMap.end()) {
    // this should never throw either
    throw std::runtime_error(
        "IsFriend: could not find a friend for this position");
  }

  const uset<TileType> &friends = it2->second;
  return friends.find(type) != friends.end();
}

void Propagate(vector<GridCell> &grid) {
  std::queue<size_t> propagationQ;

  for (size_t index = 0; index < grid.size(); index++) {
    if (!grid[index].collapsed) {
      propagationQ.push(index);
    }
  }

  while (!propagationQ.empty()) {
    size_t index = propagationQ.front();
    propagationQ.pop();

    int i = index % UNITS;
    int j = index / UNITS;

    const vector<std::pair<Position, int>> neighbors = {
        {Position::Top, (j < UNITS - 1 ? i + (j + 1) * UNITS : -1)},
        {Position::Bottom, (j > 0 ? i + (j - 1) * UNITS : -1)},
        {Position::Left, (i > 0 ? (i - 1) + j * UNITS : -1)},
        {Position::Right, (i < UNITS - 1 ? (i + 1) + j * UNITS : -1)},
    };

    GridCell &cell = grid[index];
    uset<TileType> updatedStates = cell.states;
    for (const auto &[position, neighborIndex] : neighbors) {
      if (neighborIndex == -1)
        continue; // Skip invalid neighbors

      GridCell &adjCell = grid[neighborIndex];

      uset<TileType> validStates;
      for (auto &type : updatedStates) {
        if (IsFriend(type, position, adjCell)) {
          validStates.insert(type);
        }
      }

      if (!validStates.empty())
        updatedStates = validStates;
    }

    // If the states were updated, push neighbors back to the queue
    if (updatedStates != cell.states) {
      cell.states = updatedStates;

      if (cell.states.size() == 1) {
        cell.collapsed = true;
      } else {
        // It means the states has changed but we can choose freely
        // from all of them
        auto pick = RandomElement(cell.states.begin(), cell.states.end());
        cell.states = uset<TileType>{*pick};
        cell.collapsed = true;
      }

      for (const auto &[_, neighborIndex] : neighbors) {
        if (neighborIndex != -1 && !grid[neighborIndex].collapsed) {
          propagationQ.push(neighborIndex);
        }
      }
    }
  }
}

void Draw(sf::RenderWindow &window, vector<GridCell> &grid) {
  Propagate(grid);
  for (int j = 0; j < UNITS; j++) {
    for (int i = 0; i < UNITS; i++) {
      GridCell &cell = grid[i + j * UNITS];
      if (cell.collapsed) {
        // Only one option state
        // std::cout << i << ", " << j << std::endl;
        TileType type = *cell.states.begin();
        cell.tile = std::make_unique<Tile>(type, i, j);
        cell.tile->SetPosition(i * PIXEL_SIZE * SCALE, j * PIXEL_SIZE * SCALE);
        cell.tile->sprite.setScale(SCALE, SCALE);
        window.draw(cell.tile->sprite);
      }
    }
  }
}

int main() {
  srand(time(nullptr));
  vector<GridCell> grid(UNITS * UNITS);
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "WFC");
  window.setVerticalSyncEnabled(true);

  // Simple check to see if we lower the number of states of two cells,
  // the first tile is always draw on either one of them
  // grid[0].states = {Wall_Void, Floor};
  // grid[2].states = {Wall_Void, Floor};

  int counter = 0;
  for (auto &cell : grid) {
    cell.index = counter;
    counter++;
  }

  float wait = 2.0f;

  HandleGrid(grid);
  sf::Time time = sf::seconds(wait);

  while (window.isOpen()) {
    sf::Event event;
    if (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();
    Draw(window, grid);
    sf::sleep(time);
    window.display();
  }
  return EXIT_SUCCESS;
}
