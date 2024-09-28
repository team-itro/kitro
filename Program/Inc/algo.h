#ifndef INC_ALGO_H_
#define INC_ALGO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "entry.h"
#define ROWS 16
#define COLUMNS 16

// define bit masks for walls (first 4 bits)
#define NORTH_WALL (1 << 7)
#define EAST_WALL (1 << 6)
#define WEST_WALL (1 << 5)
#define SOUTH_WALL (1 << 4)

// define bit masks for accessibility (last 4 bits)
#define NORTH_ACCESS (1 << 3)
#define EAST_ACCESS (1 << 2)
#define WEST_ACCESS (1 << 1)
#define SOUTH_ACCESS (1 << 0)
// extern int flood[ROWS][COLUMNS];
// extern int backFlood[ROWS][COLUMNS];
// extern int cells[ROWS][COLUMNS];

// void updateWalls(struct coordinate point, int orient, bool L, bool R, bool
// F); void floodFill(struct coordinate p, struct coordinate prev); char
// toMove(struct coordinate p, struct coordinate prevPos, int orient); char
// toMoveBack(struct coordinate p, struct coordinate prevPos, int orient); void
// backtrack(); int orientation(int orient, char turning); struct coordinate
// updateCoordinates(struct coordinate coordi, int orient); void
// forwardtrack(struct coordinate dumXY, struct coordinate dumXY_prev,
//                   int dumOrient);

#ifdef __cplusplus
}
#endif

#endif /* INC_ALGO_H_ */
