#include "include/tiles.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

const int PIXEL_SIZE = 16;

const int UNITS = 64;
const float SCALE_X = (float)WINDOW_WIDTH / (UNITS * PIXEL_SIZE);
const float SCALE_Y = (float)WINDOW_HEIGHT / (UNITS * PIXEL_SIZE);
const float SCALE = std::min(SCALE_X, SCALE_Y);

size_t HandleGrid(std::vector<GridCell> &grid, bool &cerror) {
  std::vector<size_t> indices;

  // Filter out collapsed cells and collect indices of uncollapsed cells
  for (size_t i = 0; i < grid.size(); ++i) {
    if (!grid[i].collapsed) {
      indices.push_back(i);
    }
  }

  // Sort indices by the number of possible states
  std::sort(indices.begin(), indices.end(), [&grid](size_t a, size_t b) {
    return grid[a].states.Size() < grid[b].states.Size();
  });

  // Get the minimum number of states
  size_t minStates = grid[indices[0]].states.Size();

  // Find the index where the number of states exceeds the minimum
  auto it = std::find_if(indices.begin(), indices.end(),
                         [&grid, minStates](size_t idx) {
                           return grid[idx].states.Size() > minStates;
                         });

  // Shuffle the range of cells with the minimum number of states
  std::shuffle(indices.begin(), it, std::default_random_engine(rand()));

  // Select the first index from the shuffled range
  size_t randomPick = indices[0];
  GridCell &cell = grid[randomPick];

  // Check for deadlock
  if (cell.states.Empty()) {
    cerror = true;
    return randomPick;
  }

  // Collapse the cell and mark it as collapsed
  cell.states.Collapse();
  cell.collapsed = true;

  return randomPick;
}

std::pair<size_t, size_t> GetIncrement(Position direction) {
  size_t dx = 0, dy = 0;
  switch (direction) {
  case Position::Top:
    dx = 0;
    dy = -1;
    break;
  case Position::Bottom:
    dx = 0;
    dy = 1;
    break;
  case Position::Left:
    dx = -1;
    dy = 0;
    break;
  case Position::Right:
    dx = 1;
    dy = 0;
    break;
  case Position::TopLeft:
    dx = -1;
    dy = -1;
    break;
  case Position::TopRight:
    dx = 1;
    dy = -1;
    break;
  case Position::BottomLeft:
    dx = -1;
    dy = 1;
    break;
  case Position::BottomRight:
    dx = 1;
    dy = 1;
    break;
  case Position::Null:
    throw std::runtime_error(
        "GetIncrement: Position::Null cannot be converted into "
        "an increment");
  }

  return std::make_pair(dx, dy);
}

struct Influences {
  unsigned int generation;
  size_t index;
  umap<size_t, Position> influencedBy;

  Influences(size_t index) : index(index) {}
  Influences(unsigned int gen, size_t index, umap<size_t, Position> infl)
      : generation(gen), index(index), influencedBy(infl) {}

  Position GetOppositePosition(size_t influencingIndex) {
    if (influencedBy.find(influencingIndex) == influencedBy.end()) {
      return Position::Null;
    }

    switch (influencedBy.at(influencingIndex)) {
    case Position::Top:
      return Position::Bottom;
    case Position::Bottom:
      return Position::Top;
    case Position::Left:
      return Position::Right;
    case Position::Right:
      return Position::Left;
    case Position::TopRight:
      return Position::BottomLeft;
    case Position::TopLeft:
      return Position::BottomRight;
    case Position::BottomRight:
      return Position::TopLeft;
    case Position::BottomLeft:
      return Position::TopRight;
    default:
      return Position::Null;
    }
  }
};

void Propagate(vector<GridCell> &grid, size_t collapsedIndex) {
  std::deque<Influences> generationsQ;
  uset<size_t> processed;
  int zerothGen = 0;

  const vector<Position> &positions = {
      Position::Top,        Position::Bottom,     Position::Left,
      Position::Right,      Position::TopLeft,    Position::TopRight,
      Position::BottomLeft, Position::BottomRight};

  int i = collapsedIndex % UNITS;
  int j = collapsedIndex / UNITS;

  if (!grid[collapsedIndex].collapsed) {
    std::cerr << "Exiting early because passed collapsedIndex does not refer "
                 "to a collapsed cell"
              << std::endl;
    std::exit(EXIT_FAILURE);
  }


  // Mark the collapsed index as proccesed
  processed.insert(collapsedIndex);
  for (const Position &pos : positions) {
    auto [dx, dy] = GetIncrement(pos);
    int x = i + dx, y = j + dy;
    if (x >= 0 && x < UNITS && y >= 0 && y < UNITS) {
      size_t index = x + y * UNITS;
      umap<size_t, Position> influencedBy = {{collapsedIndex, pos}};
      Influences influenced(zerothGen + 1, index, influencedBy);
      generationsQ.push_back(influenced);
    }
  }

  while (!generationsQ.empty()) {
    Influences influenced = generationsQ.front();
    generationsQ.pop_front();
    processed.insert(influenced.index);

    GridCell &influencedCell = grid[influenced.index];
    if (influencedCell.collapsed) {
      continue;
    }

    umap<TileType, unsigned int> occurrences;
    for (const auto &[influencingIndex, position] : influenced.influencedBy) {
      // Gets all possible states for this influencing index
      States influencingIndexStates = grid[influencingIndex].states;

      if (influencingIndexStates.Empty()) {
        break;
      }


      if (influencingIndexStates.Size() > 1) {
        for (const auto &[type, _] : influencingIndexStates.weights) {
          // Log the current type being processed

          const umap<Position, uset<TileType>> &allFriends =
              TileTypeToFriends.find(type)->second;

          // Log all positional friends for this type

          const uset<TileType> &positionalFriends =
              allFriends.find(position)->second;

          // Log the specific friends for the current position
          for (const TileType &possibleType : positionalFriends) {
            occurrences[possibleType]++;
          }
        }
      } else if (influencingIndexStates.Size() == 1) {
        const umap<Position, uset<TileType>> &allFriends =
            TileTypeToFriends.find(influencingIndexStates.collapsedState)
                ->second;


        const uset<TileType> &positionalFriends =
            allFriends.find(position)->second;

        // Log the specific friends for the current position
        for (const TileType &possibleType : positionalFriends) {
          occurrences[possibleType]++;
        }
      }
    }


    // Remove states that are impossible to be in according to the neighbors
    for (const auto &[type, _] : influencedCell.states.Get()) {
      if (occurrences.find(type) == occurrences.end()) {
        influencedCell.states.RemoveState(type);
      }
    }

    // Update the weight for the remaining states based on the neighbors'
    // occurrences
    for (const auto &[type, occ] : occurrences) {
      if (influencedCell.states.HasState(type)) {
        influencedCell.states.Insert(type, static_cast<double>(occ));
      }
    }

    // Since we are inserting new values, we must normalize at the end
    influencedCell.states.Normalize();

    // We must also check if the number of states left is one, and if so,
    // we collapse the cell
    if (influencedCell.states.Size() == 1) {
      influencedCell.states.Collapse();
      influencedCell.collapsed = true;
    }

    int i = influenced.index % UNITS;
    int j = influenced.index / UNITS;

    for (const Position &pos : positions) {
      // Enqueue neighbors of influenced based on the criteria
      // of not being processed yet. If it is in the queue, check
      // which generation it is from
      auto [dx, dy] = GetIncrement(pos);
      int x = i + dx, y = j + dy;
      if (x < 0 || x >= UNITS || y < 0 || y >= UNITS)
        continue;

      size_t nextIndex = x + y * UNITS;
      if (processed.find(nextIndex) != processed.end())
        continue;

      auto it = std::find_if(generationsQ.begin(), generationsQ.end(),
                             [nextIndex](const Influences &influence) {
                               return influence.index == nextIndex;
                             });

      // if the next index already exists in the queue
      if (it != generationsQ.end()) {
        // I must check if the nextIndex in queue generation is larger than
        // currentGen and if so, we can mark the influenced.index as influencing
        // index of nextIndex
        if ((*it).generation > influenced.generation) {
          (*it).influencedBy[influenced.index] = pos;
        }
      } else {
        // If its not in the deque, we simply add as influencing index and
        // enqueu the nextIndex
        umap<size_t, Position> influencedBy = {{influenced.index, pos}};
        Influences influencedNeighbor(influenced.generation + 1, nextIndex,
                                      influencedBy);
        generationsQ.push_back(influencedNeighbor);
      }
    }
  }
}

bool AllCollapsed(vector<GridCell> &grid) {
  return std::all_of(grid.begin(), grid.end(),
                     [](const GridCell &cell) { return cell.collapsed; });
}

void Draw(sf::RenderWindow &window, vector<GridCell> &grid) {
  for (int j = 0; j < UNITS; j++) {
    for (int i = 0; i < UNITS; i++) {
      GridCell &cell = grid[i + j * UNITS];
      if (cell.collapsed) {
        // Only one option state
        // std::cout << i << ", " << j << std::endl;
        TileType type = cell.states.collapsedState;
        cell.tile = std::make_unique<Tile>(type, i, j);
        cell.tile->SetPosition(i * PIXEL_SIZE * SCALE, j * PIXEL_SIZE * SCALE);
        cell.tile->sprite.setScale(SCALE, SCALE);
        window.draw(cell.tile->sprite);
      }
    }
  }
}

void PrintGridStates(const vector<GridCell> &grid) {
  for (size_t j = 0; j < UNITS; ++j) {
    for (size_t i = 0; i < UNITS; ++i) {
      const GridCell &cell = grid[i + j * UNITS];
      if (cell.collapsed) {
        // If the cell is collapsed, show its state
        if (cell.states.Get().size() != 1) {
          size_t stateSize = cell.states.Get().size();
          std::cerr << "Problem! Collapsed cell have " << stateSize
                    << " states!" << std::endl;
        }
        TileType collapsedState = cell.states.collapsedState;
        std::cout << std::setw(3) << "(c) " << collapsedState << " ";
      } else {
        // If the cell is not collapsed, show the number of states
        std::cout << std::setw(3) << "(u) " << cell.states.Get().size() << " ";
      }
    }
    std::cout << "\n";
  }
  std::cout << std::string(50, '-') << "\n"; // Separator for better readability
}

int main() {
  srand(time(nullptr));
  vector<GridCell> grid(UNITS * UNITS);
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "WFC");
  window.setVerticalSyncEnabled(true);

  int counter = 0;
  for (auto &cell : grid) {
    cell.index = counter;
    cell.states.Initialize();
    counter++;
  }

  bool cerror = false;

  while (!AllCollapsed(grid)) {
    // Attempt to handle the grid and collapse a cell
    int collapsedIndex = HandleGrid(grid, cerror);

    // If no valid cell could be collapsed
    if (cerror) {
      grid[collapsedIndex].states.Insert(TileType::Wall_Void, 1.0);
      grid[collapsedIndex].states.Collapse();
      grid[collapsedIndex].collapsed = true;
      cerror = false;
      continue;
    }

    // Propagate changes from the collapsed index
    Propagate(grid, collapsedIndex);

    // Debug: Print the current grid states after propagation
    // PrintGridStates(grid);
  }

  std::cout << "all collapsed" << std::endl;

  bool redraw = true;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    if (redraw) {
      window.clear();
      Draw(window, grid);
      redraw = false;
    }
    window.display();

    sf::sleep(sf::milliseconds(16));
  }
  return EXIT_SUCCESS;
}
