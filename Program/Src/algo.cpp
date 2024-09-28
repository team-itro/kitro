// algo.cpp
// author : thuvasooriya

#include "algo.h"
#include "CONSTANTS.h"
#include <iostream>
#include <queue>
#include <stdbool.h>
#include <string>

// maze: each cell is 8 bits
uint8_t floodfill[ROWS][COLUMNS] = {
    {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
    {13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13},
    {12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12},
    {11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11},
    {10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10},
    {9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9},
    {8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8},
    {7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7},
    {7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7},
    {8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8},
    {9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9},
    {10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10},
    {11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11},
    {12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12},
    {13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13},
    {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
};

int8_t cells[ROWS][COLUMNS];

// Initialize the maze with walls and no accessibility
void initialize_maze(void)
{
  // Initialize all cells with no walls and no accessibility
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      cells[i][j] = -1; // No walls, no accessibility
    }
  }
}

void update_maze(Coordinate point, Compass orient, bool L, bool R, bool F)
{
  if ((L && R) && F) {
    if (orient == 0) {
      cells[point.y][point.x] = 13;
    } //|-|
    else if (orient == 1) {
      cells[point.y][point.x] = 12;
    } //_-|
    else if (orient == 2) {
      cells[point.y][point.x] = 11;
    } //|_|
    else if (orient == 3) {
      cells[point.y][point.x] = 14;
    } //|-_
  } else if ((L && R) && (!F)) {
    if (orient == 0) {
      cells[point.y][point.x] = 9;
    } //| |
    else if (orient == 1) {
      cells[point.y][point.x] = 10;
    } //_-
    else if (orient == 2) {
      cells[point.y][point.x] = 9;
    } //| |
    else if (orient == 3) {
      cells[point.y][point.x] = 10;
    } //_-
  } else if ((L && F) && (!R)) {
    if (orient == 0) {
      cells[point.y][point.x] = 8;
    } //|-
    else if (orient == 1) {
      cells[point.y][point.x] = 7;
    } //-|
    else if (orient == 2) {
      cells[point.y][point.x] = 6;
    } //_|
    else if (orient == 3) {
      cells[point.y][point.x] = 5;
    } //|_
  } else if ((R && F) && (!L)) {
    if (orient == 0) {
      cells[point.y][point.x] = 7;
    } //-|
    else if (orient == 1) {
      cells[point.y][point.x] = 6;
    } //_|
    else if (orient == 2) {
      cells[point.y][point.x] = 5;
    } //|_
    else if (orient == 3) {
      cells[point.y][point.x] = 8;
    } //|-
  } else if (F) {
    if (orient == 0) {
      cells[point.y][point.x] = 2;
    } //-
    else if (orient == 1) {
      cells[point.y][point.x] = 3;
    } // |
    else if (orient == 2) {
      cells[point.y][point.x] = 4;
    } //_
    else if (orient == 3) {
      cells[point.y][point.x] = 1;
    } //|
  } else if (L) {
    if (orient == 0) {
      cells[point.y][point.x] = 1;
    } //|
    else if (orient == 1) {
      cells[point.y][point.x] = 2;
    } //-
    else if (orient == 2) {
      cells[point.y][point.x] = 3;
    } // |
    else if (orient == 3) {
      cells[point.y][point.x] = 4;
    } //_
  } else if (R) {
    if (orient == 0) {
      cells[point.y][point.x] = 3;
    } // |
    else if (orient == 1) {
      cells[point.y][point.x] = 4;
    } //_
    else if (orient == 2) {
      cells[point.y][point.x] = 1;
    } //|
    else if (orient == 3) {
      cells[point.y][point.x] = 2;
    } //-
  } else {
    cells[point.y][point.x] = 0; //
  }
}

bool is_accessible(Coordinate p, Coordinate p1)
{
  if (p1.x < 0 || p1.y < 0 || p1.x >= ROWS || p1.y >= COLUMNS) {
    return false;
  }

  if (p.x == p1.x) {
    if (p.y > p1.y) {
      if (cells[p.y][p.x] == 4 || cells[p.y][p.x] == 5 ||
          cells[p.y][p.x] == 6 || cells[p.y][p.x] == 10 ||
          cells[p.y][p.x] == 11 || cells[p.y][p.x] == 12 ||
          cells[p.y][p.x] == 14) {
        return false;
      }

      else {
        return true;
      }
    } else {
      if (cells[p.y][p.x] == 2 || cells[p.y][p.x] == 7 ||
          cells[p.y][p.x] == 8 || cells[p.y][p.x] == 10 ||
          cells[p.y][p.x] == 12 || cells[p.y][p.x] == 13 ||
          cells[p.y][p.x] == 14) {
        return false;
      }

      else {
        return true;
      }
    }
  } else if (p.y == p1.y) {
    if (p.x > p1.x) {
      if (cells[p.y][p.x] == 1 || cells[p.y][p.x] == 5 ||
          cells[p.y][p.x] == 8 || cells[p.y][p.x] == 9 ||
          cells[p.y][p.x] == 11 || cells[p.y][p.x] == 13 ||
          cells[p.y][p.x] == 14) {
        return false;
      } else {
        return true;
      }
    } else {
      if (cells[p.y][p.x] == 3 || cells[p.y][p.x] == 6 ||
          cells[p.y][p.x] == 7 || cells[p.y][p.x] == 9 ||
          cells[p.y][p.x] == 11 || cells[p.y][p.x] == 12 ||
          cells[p.y][p.x] == 13) {
        return false;
      } else {
        return true;
      }
    }
  } else {
    return false;
  }
}

struct surroundCoor getSurrounds(Coordinate p)
{
  struct surroundCoor surCoor;
  surCoor.N.x = p.x;
  surCoor.N.y = p.y + 1;

  surCoor.S.x = p.x;
  surCoor.S.y = p.y - 1;

  surCoor.W.x = p.x - 1;
  surCoor.W.y = p.y;

  surCoor.E.x = p.x + 1;
  surCoor.E.y = p.y;

  if (surCoor.N.x >= ROWS) {
    surCoor.N.x = -1;
  }
  if (surCoor.W.y >= COLUMNS) {
    surCoor.W.y = -1;
  }
  return surCoor;
}

Coordinate updateCoordinates(Coordinate coordi, Compass orient)
{
  if (orient == 0) {
    coordi.y += 1;
  }
  if (orient == 1) {
    coordi.x += 1;
  }
  if (orient == 2) {
    coordi.y -= 1;
  }
  if (orient == 3) {
    coordi.x -= 1;
  }
  return coordi;
}

Compass orientation(Compass orient, DriveState turning)
{
  if (turning == TL) { // Turning Left
    orient = (orient == NORTH) ? WEST : (Compass)(orient - 1);
  }

  else if (turning == TR) { // Turning Right
    orient = (orient == WEST) ? NORTH : (Compass)(orient + 1);
  }

  else if (turning == BK) { // U-turn (Back)
    orient = (Compass)((orient + 2) % 4);
  }

  return orient;
}

// int orientation(int orient, char turning)
// {
//   if (turning == 'L') {
//     orient -= 1;
//     if (orient == -1) {
//       orient = 3;
//     }
//   }
//
//   else if (turning == 'R') {
//     orient += 1;
//     if (orient == 4) {
//       orient = 0;
//     }
//   }
//
//   else if (turning == 'B') {
//     if (orient == 0) {
//       orient = 2;
//     } else if (orient == 1) {
//       orient = 3;
//     } else if (orient == 2) {
//       orient = 0;
//     } else if (orient == 3) {
//       orient = 1;
//     }
//   }
//   return orient;
// }

bool isConsistant(Coordinate p)
{
  struct surroundCoor surr = getSurrounds(p);
  int minVals[4] = {-1, -1, -1, -1};
  if (surr.N.x >= 0 && surr.N.y >= 0) {
    if (is_accessible(p, surr.N)) {
      minVals[0] = floodfill[surr.N.y][surr.N.x];
    }
  }
  if (surr.E.x >= 0 && surr.E.y >= 0) {
    if (is_accessible(p, surr.E)) {
      minVals[1] = floodfill[surr.E.y][surr.E.x];
    }
  }
  if (surr.S.x >= 0 && surr.S.y >= 0) {
    if (is_accessible(p, surr.S)) {
      minVals[2] = floodfill[surr.S.y][surr.S.x];
    }
  }
  if (surr.W.x >= 0 && surr.W.y >= 0) {
    if (is_accessible(p, surr.W)) {
      minVals[3] = floodfill[surr.W.y][surr.W.x];
    }
  }
  int val = floodfill[p.y][p.x];
  int minCount = 0;
  for (int i = 0; i < 4; i++) {
    if (minVals[i] == val - 1 && minVals[i] != -1) {
      minCount++;
    }
  }

  if (minCount > 0 || val == 0) {
    return true;
  } else {
    return false;
  }
}

void makeConsistant(Coordinate p)
{
  struct surroundCoor surr = getSurrounds(p);
  int minVals[4] = {-1, -1, -1, -1};
  if (surr.N.y >= 0 && surr.N.x >= 0) {
    if (is_accessible(p, surr.N)) {
      minVals[0] = floodfill[surr.N.y][surr.N.x];
    }
  }
  if (surr.E.y >= 0 && surr.E.x >= 0) {
    if (is_accessible(p, surr.E)) {
      minVals[1] = floodfill[surr.E.y][surr.E.x];
    }
  }
  if (surr.S.y >= 0 && surr.S.x >= 0) {
    if (is_accessible(p, surr.S)) {
      minVals[2] = floodfill[surr.S.y][surr.S.x];
    }
  }
  if (surr.W.y >= 0 && surr.W.x >= 0) {
    if (is_accessible(p, surr.W)) {
      minVals[3] = floodfill[surr.W.y][surr.W.x];
    }
  }
  int minimum = 1000;
  for (int i = 0; i < 4; i++) {
    if (minVals[i] == -1) {
      minVals[i] = 1000;
    }
    if (minVals[i] < minimum) {
      minimum = minVals[i];
    }
  }
  floodfill[p.y][p.x] = minimum + 1;
}

void floodFill(Coordinate p, Coordinate prev)
{
  if (!isConsistant(p)) {
    floodfill[p.y][p.x] = floodfill[prev.y][prev.x] + 1;
  }

  std::queue<Coordinate> q;
  q.push(p);

  struct surroundCoor surr = getSurrounds(p);
  if (surr.N.x >= 0 && surr.N.y >= 0) {
    if (is_accessible(p, surr.N)) {
      q.push(surr.N);
    }
  }
  if (surr.E.x >= 0 && surr.E.y >= 0) {
    if (is_accessible(p, surr.E)) {
      q.push(surr.E);
    }
  }
  if (surr.S.x >= 0 && surr.S.y >= 0) {
    if (is_accessible(p, surr.S)) {
      q.push(surr.S);
    }
  }
  if (surr.W.x >= 0 && surr.W.y >= 0) {
    if (is_accessible(p, surr.W)) {
      q.push(surr.W);
    }
  }

  while (!q.empty()) {
    Coordinate crun = q.front();
    q.pop();
    if (isConsistant(crun)) {

    } else {
      makeConsistant(crun);
      q.push(crun);
      struct surroundCoor surr = getSurrounds(crun);
      if (surr.N.y >= 0 && surr.N.x >= 0) {
        if (is_accessible(crun, surr.N)) {
          q.push(surr.N);
        }
      }
      if (surr.E.y >= 0 && surr.E.x >= 0) {
        if (is_accessible(crun, surr.E)) {
          q.push(surr.E);
        }
      }
      if (surr.S.y >= 0 && surr.S.x >= 0) {
        if (is_accessible(crun, surr.S)) {
          q.push(surr.S);
        }
      }
      if (surr.W.y >= 0 && surr.W.x >= 0) {
        if (is_accessible(crun, surr.W)) {
          q.push(surr.W);
        }
      }
    }
  }
}

DriveState toMove(Coordinate p, Coordinate prevPos, Compass orient)
{
  struct surroundCoor surr = getSurrounds(p);
  int minVals[4] = {1000, 1000, 1000, 1000};
  int prevDir = 0;
  if (surr.N.y >= 0 && surr.N.x >= 0) {
    if (is_accessible(p, surr.N)) {
      minVals[0] = floodfill[surr.N.y][surr.N.x];
      if (surr.N.x == prevPos.x && surr.N.y == prevPos.y) {
        prevDir = 0;
      }
    }
  }
  if (surr.E.y >= 0 && surr.E.x >= 0) {
    if (is_accessible(p, surr.E)) {
      minVals[1] = floodfill[surr.E.y][surr.E.x];
      if (surr.E.x == prevPos.x && surr.E.y == prevPos.y) {
        prevDir = 1;
      }
    }
  }
  if (surr.S.y >= 0 && surr.S.x >= 0) {
    if (is_accessible(p, surr.S)) {
      minVals[2] = floodfill[surr.S.y][surr.S.x];
      if (surr.S.x == prevPos.x && surr.S.y == prevPos.y) {
        prevDir = 2;
      }
    }
  }
  if (surr.W.y >= 0 && surr.W.x >= 0) {
    if (is_accessible(p, surr.W)) {
      minVals[3] = floodfill[surr.W.y][surr.W.x];
      if (surr.W.x == prevPos.x && surr.W.y == prevPos.y) {
        prevDir = 3;
      }
    }
  }

  int minimum = 1000;
  int noMovements = 0;
  for (int i = 0; i < 4; i++) {
    if (minVals[i] != 1000) {
      noMovements++;
    }
  }

  int minCell = 0;
  for (int i = 0; i < 4; i++) {
    if (minVals[i] < minimum) {
      if (noMovements == 1) {
        minimum = minVals[i];
        minCell = i;
      } else {
        if (i == prevDir) {

        } else {
          minimum = minVals[i];
          minCell = i;
        }
      }
    }
  }

  // using namespace std;
  // string line = "";
  // for (int b = 0; b < 4; b++) {
  //   line = line + to_string(minVals[b]) + "\t";
  // }
  // string minCellS = to_string(minCell);

  if (minCell == orient) {
    return FW;
  } else if (minCell == orient - 1 || minCell == orient + 3) {
    return TL;
  } else if (minCell == orient + 1 || minCell == orient - 3) {
    return TR;
  } else {
    return BK;
  }
}
// int flood[ROWS][COLUMNS] = {
//     {2, 1, 1, 2},
//     {1, 0, 0, 1},
//     {1, 0, 0, 1},
//     {2, 1, 1, 2},
// };
//
// int cells[ROWS][COLUMNS] = {
//     {-1, -1, -1, -1},
//     {-1, -1, -1, -1},
//     {-1, -1, -1, -1},
//     {-1, -1, -1, -1},
// };
// int backFlood[ROWS][COLUMNS] = {
//     {-1, -1, -1, -1},
//     {-1, -1, -1, -1},
//     {-1, -1, -1, -1},
//     {-1, -1, -1, -1},
// };

// int flood12[ROWS][COLUMNS] = {
//     {12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12},
//     {11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11},
//     {10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10},
//     {9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9},
//     {8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8},
//     {7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7},
//     {6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6},
//     {6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6},
//     {7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7},
//     {8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8},
//     {9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9},
//     {10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10},
//     {11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11},
//     {12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12},
// };
//
// int flood16[ROWS][COLUMNS] = {
//     {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
//     {13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13},
//     {12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12},
//     {11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11},
//     {10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10},
//     {9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9},
//     {8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8},
//     {7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7},
//     {7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7},
//     {8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8},
//     {9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9},
//     {10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10},
//     {11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11},
//     {12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12},
//     {13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13},
//     {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
// };

// int cells[ROWS][COLUMNS] = {
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};
//
// int backFlood[ROWS][COLUMNS] = {
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
//     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};
