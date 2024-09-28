#ifndef INC_ALGO_H_
#define INC_ALGO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "entry.h"

#define ROWS 16
#define COLUMNS 16

// // define bit masks for walls (first 4 bits)
// #define NORTH_WALL (1 << 7)
// #define EAST_WALL (1 << 6)
// #define WEST_WALL (1 << 5)
// #define SOUTH_WALL (1 << 4)
//
// // define bit masks for accessibility (last 4 bits)
// #define NORTH_ACCESS (1 << 3)
// #define EAST_ACCESS (1 << 2)
// #define WEST_ACCESS (1 << 1)
// #define SOUTH_ACCESS (1 << 0)

extern uint8_t floodfill[ROWS][COLUMNS];
extern const uint8_t floodfillconst[ROWS][COLUMNS];
// extern int backFlood[ROWS][COLUMNS];
extern int8_t cells[ROWS][COLUMNS];

struct surroundCoor {
  Coordinate N;
  Coordinate S;
  Coordinate W;
  Coordinate E;
};

void initialize_maze(void);
void update_maze(Coordinate point, Compass orient, bool L, bool R, bool F);
bool is_accessible(Coordinate p, Coordinate p1);
DriveState toMove(Coordinate p, Coordinate prevPos, Compass orient);
void floodFill(Coordinate p, Coordinate prev);
Compass orientation(Compass orient, DriveState turning);
Coordinate updateCoordinates(Coordinate coordi, Compass orient);

#ifdef __cplusplus
}
#endif

#endif /* INC_ALGO_H_ */
