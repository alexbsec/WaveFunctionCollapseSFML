#ifndef _CONFIG_WFC_HPP
#define _CONFIG_WFC_HPP

#include <array>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T, typename P> using umap = std::unordered_map<T, P>;
template <typename T> using vector = std::vector<T>;
template <typename T> using uset = std::unordered_set<T>;
using string = std::string;

const string SPRITESHEET_PATH = "assets/Tileset.png";

// View and screen
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// World size in tiles
const int WORLD_X = 64;
const int WORLD_Y = 64;

// Spritesheet tile original size and scale factor
const int TILE_SIZE = 16;
const int SCALE_FACTOR = 2;

// Directions
enum Direction { Top, Down, Left, Right };

// Tile Types
enum TileType {
  /* WALLS */
  Wall_TopLeftCorner,
  Wall_TopRightCorner,
  Wall_BottomLeftCorner,
  Wall_BottomRightCorner,
  Wall_TopHorizontalLeft,
  Wall_TopHorizontalMiddle,
  Wall_TopHorizontalRight,
  Wall_BottomHorizontalLeft,
  Wall_BottomHorizontalMiddle,
  Wall_BottomHorizontalRight,
  Wall_LeftVerticalTop,
  Wall_LeftVerticalMiddle,
  Wall_LeftVerticalBottom,
  Wall_RightVerticalTop,
  Wall_RightVerticalMiddle,
  Wall_RightVerticalBottom,
  Wall_TopHorizontalPassageLeft,
  Wall_TopHorizontalPassageRight,
  Wall_BottomHorizontalPassageLeft,
  Wall_BottomHorizontalPassageRight,
  Wall_LeftVerticalPassageTop,
  Wall_LeftVerticalPassageBottom,
  Wall_RightVerticalPassageTop,
  Wall_RightVerticalPassageBottom,
  /* Holes and Voids */
  Wall_Void,
  Wall_LeftHoleSimple,
  Wall_HoleStairs,
  Wall_RightHoleSimple,
  Wall_HoleStairsBroken,

  Floor_TopLeftCorner,
  Floor_TopMiddle,
  Floor_TopRightCorner,
  Floor_MiddleLeft,
  Floor_MiddleMiddle,
  Floor_MiddleRight,
  Floor_BottomLeftCorner,
  Floor_BottomMiddle,
  Floor_BottomRightCorner,
  Floor_Wildcard,
};

const umap<TileType, std::array<int, 2>> TILE_SPRITESHEET_POSITION = {

};

const umap<TileType, umap<Direction, TileType>> TILE_RULES = {
  {Wall_TopLeftCorner,
    {
      {Top, Wall_Void},
      {Down, Wall_LeftVerticalTop},
      {Right, Wall_TopHorizontalLeft},
      {Left, Wall_Void},
    }
  },
  {Wall_TopRightCorner,
    {
      {Top, Wall_Void},
      {Down, Wall_RightVerticalTop},
      {Right, Wall_Void},
      {Left, Wall_TopHorizontalRight},
    }
  },
  {Wall_BottomLeftCorner,
    {
      {Top, Wall_LeftVerticalBottom},
      {Down, Wall_Void},
      {Right, Wall_BottomHorizontalLeft},
      {Left, Wall_Void},
    }
  },
  {Wall_BottomRightCorner,
    {
      {Top, Wall_RightVerticalBottom},
      {Down, Wall_Void},
      {Right, Wall_Void},
      {Left, Wall_BottomHorizontalRight},
    }
  },
  {Wall_LeftVerticalTop,
    {
      {Top, Wall_TopLeftCorner},
      {Down, Wall_LeftVerticalMiddle},
      {Left, Wall_Void},
      {Right, Floor_TopLeftCorner},
    }
  },
  {Wall_LeftVerticalMiddle,
    {
      {Top, Wall_LeftVerticalTop},
      {Down, Wall_LeftVerticalBottom},
      {Left, Wall_Void},
      {Right, Floor_TopLeftCorner},
    }
  },
  {Wall_LeftVerticalPassageTop,
    {
      {Top, Wall_LeftVerticalTop},
      {Down, Wall_LeftVerticalPassageBottom},
      {Left, Floor_MiddleRight},
      {Right, Floor_MiddleLeft},
    }
  },
  {Wall_LeftVerticalPassageBottom,
    {
      {Top, Wall_LeftVerticalPassageTop},
      {Down, Wall_LeftVerticalBottom},
      {Left, Floor_BottomRightCorner},
      {Right, Floor_BottomLeftCorner},
    }
  },
  {Wall_LeftVerticalBottom,
    {
      {Top, Wall_LeftVerticalMiddle},
      {Down, Wall_BottomLeftCorner},
      {Left, Wall_Void},
      {Right, Floor_BottomLeftCorner},
    }
  },
  {Wall_TopHorizontalLeft,
    {
      {Top, Wall_Void},
      {Down, Floor_TopLeftCorner},
      {Left, Wall_TopLeftCorner},
      {Right, Wall_TopHorizontalMiddle},
    }
  },
  {Wall_TopHorizontalMiddle,
    {
      {Top, Wall_Void},
      {Down, Floor_TopMiddle},
      {Left, Wall_TopHorizontalLeft},
      {Right, Wall_TopHorizontalRight},
    }
  },
  {Wall_TopHorizontalRight,
    {
      {Top, Wall_Void},
      {Down, Floor_TopRightCorner},
      {Left, Wall_TopHorizontalMiddle},
      {Right, Wall_TopRightCorner},
    }
  },
  {Wall_TopHorizontalPassageLeft,
    {
      {Top, Floor_BottomLeftCorner},
      {Down, Floor_TopLeftCorner},
      {Left, Wall_TopLeftCorner},
      {Right, Floor_Wildcard},
    }
  },
  {Wall_TopHorizontalPassageLeft, 
    {
      {Top, Floor_BottomRightCorner},
      {Down, Floor_TopRightCorner},
      {Left, Floor_Wildcard},
      {Right, Wall_TopRightCorner},
    }
  },
  {Wall_RightVerticalTop,
    {
      {Top, Wall_TopRightCorner},
      {Down, Wall_RightVerticalMiddle},
      {Left, Floor_TopRightCorner},
      {Right, Wall_Void},
    }
  },
  {Wall_RightVerticalMiddle,
    {
      {Top, Wall_RightVerticalTop},
      {Down, Wall_RightVerticalBottom},
      {Left, Floor_MiddleLeft},
      {Right, Wall_Void},
    }
  },
  {Wall_RightVerticalBottom,
    {
      {Top, Wall_RightVerticalMiddle},
      {Down, Wall_BottomRightCorner},
      {Left, Floor_BottomRightCorner},
      {Right, Wall_Void},
    }
  },
  {Wall_RightVerticalPassageTop,
    {
      {Top, Wall_TopRightCorner},
      {Down, Wall_RightVerticalPassageBottom},
      {Left, Floor_TopRightCorner},
      {Right, Floor_TopLeftCorner},
    }
  },
  {Wall_RightVerticalPassageBottom,
    {
      {Top, Wall_RightVerticalPassageTop},
      {Down, Wall_RightVerticalBottom},
      {Left, Floor_MiddleRight},
      {Right, Floor_MiddleLeft},
    }
  },
  {Wall_BottomHorizontalRight,
    {
      {Top, Floor_BottomRightCorner},
      {Down, Wall_Void},
      {Left, Wall_BottomHorizontalMiddle},
      {Right, Wall_BottomRightCorner},
    }
  },
  {Wall_BottomHorizontalMiddle,
    {
      {Top, Floor_BottomMiddle},
      {Down, Wall_Void},
      {Left, Wall_BottomHorizontalLeft},
      {Right, Wall_BottomHorizontalRight},
    }
  },
  {Wall_BottomHorizontalLeft,
    {
      {Top, Floor_BottomLeftCorner},
      {Down, Wall_Void},
      {Left, Wall_BottomLeftCorner},
      {Right, Wall_BottomHorizontalMiddle},
    }
  },
  {Wall_BottomHorizontalPassageRight, 
    {
      {Top, Floor_BottomRightCorner},
      {Down, Floor_TopRightCorner},
      {Left, Floor_Wildcard},
      {Right, Wall_BottomRightCorner},
    }
  },
  {Wall_BottomHorizontalPassageLeft,
    {
      {Top, Floor_BottomLeftCorner},
      {Down, Floor_TopLeftCorner},
      {Left, Wall_BottomLeftCorner},
      {Right, Floor_Wildcard},
    }
  },
  {Wall_Void,
    {
      {Top, Wall_Void},
      {Down, Wall_Void},
      {Left, Wall_Void},
      {Right, Wall_Void},
    }
  },
  {Wall_LeftHoleSimple,
    {
      {Top, Floor_BottomLeftCorner},
      {Down, Wall_Void},
      {Left, Wall_TopRightCorner},
      {Right, Wall_HoleStairs},
    }
  },
  {Wall_HoleStairs,
    {
      {Top, Floor_BottomMiddle},
      {Down, Wall_Void},
      {Left, Wall_LeftHoleSimple},
      {Right, Wall_RightHoleSimple},
    }
  },
  {Wall_HoleStairsBroken,
    {
      {Top, Floor_BottomMiddle},
      {Down, Wall_Void},
      {Left, Wall_LeftHoleSimple},
      {Right, Wall_RightHoleSimple},
    }
  },
  {Wall_RightHoleSimple,
    {
      {Top, Floor_BottomRightCorner},
      {Down, Wall_Void},
      {Left, Wall_HoleStairs},
      {Right, Wall_TopLeftCorner},
    }
  },
  {Floor_TopLeftCorner,
    {
      {Top, Wall_TopHorizontalLeft},
      {Down, Floor_MiddleLeft},
      {Left, Wall_LeftVerticalTop},
      {Right, Floor_TopMiddle},
    }
  },
  {Floor_TopMiddle,
    {
      {Top, Wall_TopHorizontalMiddle},
      {Down, Floor_MiddleMiddle},
      {Left, Floor_TopLeftCorner},
      {Right, Floor_TopRightCorner},
    }
  },
  {Floor_TopRightCorner,
    {
      {Top, Wall_TopHorizontalRight},
      {Down, Floor_MiddleRight},
      {Left, Floor_TopMiddle},
      {Right, Wall_RightVerticalTop},
    }
  },
  {Floor_MiddleLeft,
    {
      {Top, Floor_TopLeftCorner},
      {Down, Floor_BottomLeftCorner},
      {Left, Wall_LeftVerticalMiddle},
      {Right, Floor_MiddleMiddle},
    }
  },
  {Floor_MiddleMiddle,
    {
      {Top, Floor_TopMiddle},
      {Down, Floor_BottomMiddle},
      {Left, Floor_MiddleLeft},
      {Right, Floor_MiddleRight},
    }
  },
  {Floor_MiddleRight,
    {
      {Top, Floor_TopRightCorner},
      {Down, Floor_BottomRightCorner},
      {Left, Floor_MiddleMiddle},
      {Right, Wall_RightVerticalMiddle},
    }
  },
  {Floor_BottomLeftCorner,
    {
      {Top, Floor_MiddleLeft},
      {Down, Wall_BottomHorizontalLeft},
      {Left, Wall_LeftVerticalBottom},
      {Right, Floor_BottomMiddle},
    }
  },
  {Floor_BottomMiddle,
    {
      {Top, Floor_MiddleMiddle},
      {Down, Wall_BottomHorizontalMiddle},
      {Left, Floor_BottomLeftCorner},
      {Right, Floor_BottomRightCorner},
    }
  },
  {Floor_BottomRightCorner,
    {
      {Top, Floor_MiddleRight},
      {Down, Wall_BottomHorizontalRight},
      {Left, Floor_BottomMiddle},
      {Right, Wall_RightVerticalBottom},
    }
  },
  {Floor_Wildcard,
    {
      {Top, Floor_BottomMiddle},
      {Down, Floor_TopMiddle},
      {Left, Wall_BottomHorizontalPassageLeft},
      {Right, Wall_TopHorizontalPassageRight},
    }
  }
};

#endif
