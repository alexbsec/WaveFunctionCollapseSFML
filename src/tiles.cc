#include "include/tiles.hpp"

/*
 * Wall_TopRightCorner: {
 *  Top: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  Bottom: {
 *    Wall_Vertical
 *  },
 *  Left: {
 *    Wall_Horizontal
 *  },
 *  Right: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  TopRight: {
 *    Floor,
 *    Wall_Void,
 *    Wall_BottomLeftCorner,
 *  },
 *  TopLeft: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  BottomRight: {
 *    Floor,
 *    Wall_Void,
 *  }
 *  BottomLeft: {
 *    Floor,
 *  },
 * }
 *  
 * Wall_TopLeftCorner: {
 *  Top: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  Bottom: {
 *    Wall_Vertical,
 *  },
 *  Left: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  Right: {
 *    Wall_Horizontal, 
 *  },
 *  TopRight: {
 *    Floor,
 *    Wall_Void, 
 *  },
 *  TopLeft: {
 *    Floor,
 *    Wall_Void,
 *    Wall_BottomRightCorner,
 *  },
 *  BottomRight: {
 *    Floor, 
 *  },
 *  BottomLeft: {
 *    Floor,
 *    Wall_Void
 *  }
 * }
 * 
 * Wall_BottomRightCorner: {
 *  Top: {
 *    Wall_Vertical,
 *  },
 *  Bottom: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  Left: {
 *    Wall_Horizontal,
 *  },
 *  Right: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  TopRight: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  TopLeft: {
 *    Floor,
 *  },
 *  BottomRight: {
 *    Floor,
 *    Wall_Void,
 *    Wall_TopLeftCorner,
 *  },
 *  BottomLeft: {
 *    Floor,
 *    Wall_Void,
 *  }
 * }
 *
 * Wall_BottomLeftCorner: {
 *  Top: {
 *    Wall_Vertical,
 *  },
 *  Bottom: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  Left: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  Right: {
 *    Wall_Horizontal,
 *  },
 *  TopRight: {
 *    Floor,
 *  },
 *  TopLeft: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  BottomRight: {
 *    Floor,
 *    Wall_Void
 *  },
 *  BottomLeft: {
 *    Floor,
 *    Wall_Void,
 *    Wall_TopRightCorner,
 *  }
 * }
 *
 * Wall_Vertical: {
 *  Top: {
 *    Wall_Vertical,
 *    Wall_TopRightCorner,
 *    Wall_TopLeftCorner,
 *  },
 *  Bottom: {
 *    Wall_Vertical,
 *    Wall_BottomRightCorner,
 *    Wall_BottomLeftCorner,
 *  },
 *  Left: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  Right: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  TopRight: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  TopLeft: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  BottomRight: {
 *    Floor,
 *    Wall_Void
 *  },
 *  BottomLeft: {
 *    Floor,
 *    Wall_Void
 *  }
 * }
 *
 * Wall_Horizontal: {
 *  Top: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  Bottom: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  Left: {
 *    Wall_Horizontal,
 *    Wall_TopLeftCorner,
 *    Wall_BottomLeftCorner,
 *  },
 *  Right: {
 *    Wall_Horizontal,
 *    Wall_TopRightCorner,
 *    Wall_BottomRightCorner,
 *  },
 *  TopRight: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  TopLeft: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  BottomRight: {
 *    Floor,
 *    Wall_Void,
 *  },
 *  BottomLeft: {
 *    Floor,
 *    Wall_Void,
 *  }
 * }
 *
 * Wall_Void: {
 *  Top: {
 *    Wall_Void,
 *    Wall_BottomRightCorner,
 *    Wall_BottomLeftCorner,
 *    Wall_Horizontal
 *  },
 *  Bottom: {
 *    Wall_Void,
 *    Wall_TopRightCorner,
 *    Wall_TopLeftCorner,
 *    Wall_Horizontal,
 *  },
 *  Left: {
 *    Wall_Void,
 *    Wall_TopRightCorner,
 *    Wall_BottomRightCorner,
 *    Wall_Vertical,
 *  },
 *  Right: {
 *    Wall_Void,
 *    Wall_TopLeftCorner,
 *    Wall_BottomLeftCorner,
 *    Wall_Vertical,
 *  },
 *  TopRight: {
 *    Wall_Void,
 *    Wall_TopLeftCorner,
 *    Wall_BottomLeftCorner,
 *    Wall_BottomRightCorner,
 *    Wall_Vertical,
 *    Wall_Horizontal,
 *  },
 *  TopLeft: {
 *    Wall_Void,
 *    Wall_TopRightCorner,
 *    Wall_BottomLeftCorner,
 *    Wall_BottomRightCorner,
 *    Wall_Vertical,
 *    Wall_Horizontal
 *  },
 *  BottomRight: {
 *    Wall_Void,
 *    Wall_TopLeftCorner,
 *    Wall_TopRightCorner,
 *    Wall_BottomLeftCorner,
 *    Wall_Vertical,
 *    Wall_Horizontal,
 *  },
 *  BottomLeft: {
 *    Wall_Void,
 *    Wall_TopLeftCorner,
 *    Wall_TopRightCorner,
 *    Wall_BottomRightCorner,
 *    Wall_Vertical,
 *    Wall_Horizontal,
 *  }
 * }
 *
 * Floor: {
 *  Top: {
 *    Floor,
 *    Wall_Horizontal,
 *  },
 *  Bottom: {
 *    Floor,
 *    Wall_Horizontal,
 *  },
 *  Left: {
 *    Floor,
 *    Wall_Vertical,
 *  },
 *  Right: {
 *    Floor,
 *    Wall_Vertical
 *  },
 *  TopRight: {
 *    Floor,
 *    Wall_TopRightCorner,
 *  },
 *  TopLeft: {
 *    Floor,
 *    Wall_TopLeftCorner,
 *  },
 *  BottomRight: {
 *    Floor,
 *    Wall_BottomRightCorner,
 *  },
 *  BottomLeft: {
 *    Floor,
 *    Wall_BottomLeftCorner,
 *  }
 * }
 *
 * */

uset<TileType> GetFriendTiles(TileType type, Position position) {
  uset<TileType> friendsAtPos;

}

const vector<FriendTiles *> &GetAllFriendTiles() {
  umap<Position, uset<TileType>> tileFriends;
sd
  static const vector<FriendTiles *> friends = {
      new FriendTiles(Wall_TopRightCorner,
                      uset<TileType>(Floor, Wall_TopRightCorner)),
  };
  return friends;
}
