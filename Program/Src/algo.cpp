// algo.cpp
// author : thuvasooriya

#include "algo.h"
#include <iostream>
#include <queue>
#include <stdbool.h>
#include <string>

#define MAX_ROWS 16
#define MAX_COLS 16

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
// configurable start and destination
uint8_t start_row = 0, start_col = 0;
uint8_t destination_row = 7, destination_col = 7;
uint8_t dest_size = 2; // destination area size (in terms of cells)

// maze: each cell is 8 bits
uint8_t maze[MAX_ROWS][MAX_COLS];

void initialize_maze(void);
void set_wall(int row, int col, uint8_t wall_mask);
bool is_valid_cell(int row, int col);
void flood_fill(int row, int col);
void print_maze(void);
bool is_wall_present(int row, int col, uint8_t wall_mask);
bool is_cell_accessible(int row, int col, uint8_t access_mask);

void set_accessibility(int row, int col, uint8_t access_mask);
void flood_neighbors(int row, int col);
bool is_at_destination(int row, int col);

// Initialize the maze with walls and no accessibility
void initialize_maze(void)
{
  // Initialize all cells with no walls and no accessibility
  for (int i = 0; i < MAX_ROWS; i++) {
    for (int j = 0; j < MAX_COLS; j++) {
      maze[i][j] = 0; // No walls, no accessibility
    }
  }

  // Configurable walls (based on the maze image)

  // Outer boundary walls (just an example, add as needed based on the image)
  for (int i = 0; i < MAX_COLS; i++) {
    set_wall(0, i, NORTH_WALL);            // Top row walls
    set_wall(MAX_ROWS - 1, i, SOUTH_WALL); // Bottom row walls
  }
  for (int i = 0; i < MAX_ROWS; i++) {
    set_wall(i, 0, WEST_WALL);            // Leftmost column walls
    set_wall(i, MAX_COLS - 1, EAST_WALL); // Rightmost column walls
  }

  // More specific walls based on the maze structure seen in the image

  // (Example setup)
  set_wall(0, 1, EAST_WALL);
  set_wall(1, 1, NORTH_WALL);
  // Add more walls as per the maze structure from the image...

  // Destination Area - mark central area as destination
  for (int i = destination_row; i < destination_row + dest_size; i++) {
    for (int j = destination_col; j < destination_col + dest_size; j++) {
      // Mark the destination as a special zone
      maze[i][j] |= (NORTH_ACCESS | EAST_ACCESS | WEST_ACCESS | SOUTH_ACCESS);
    }
  }
}

// Set wall in a specific direction for a cell
void set_wall(int row, int col, uint8_t wall_mask)
{
  if (is_valid_cell(row, col)) {
    maze[row][col] |= wall_mask;
  }
}

// Check if the cell coordinates are valid
bool is_valid_cell(int row, int col)
{
  return (row >= 0 && row < MAX_ROWS && col >= 0 && col < MAX_COLS);
}

// Flood fill algorithm to mark accessible cells
void flood_fill(int row, int col)
{
  if (!is_valid_cell(row, col))
    return;

  // Check if the cell has already been accessed
  if (is_cell_accessible(
          row, col, NORTH_ACCESS | EAST_ACCESS | WEST_ACCESS | SOUTH_ACCESS)) {
    return; // Already visited
  }

  // Mark current cell as accessible from all directions
  set_accessibility(row, col,
                    NORTH_ACCESS | EAST_ACCESS | WEST_ACCESS | SOUTH_ACCESS);

  // Recursively check neighboring cells
  flood_neighbors(row, col);
}
//
// // Helper function to recursively flood neighboring cells
// void flood_neighbors(int row, int col)
// {
//   // Stop flooding if at the destination
//   if (is_at_destination(row, col))
//     return;
//
//   // Flood neighboring cells only if there's no wall blocking the way
//   if (row > 0 && !is_wall_present(row, col, NORTH_WALL)) {
//     flood_fill(row - 1, col); // North
//   }
//   if (col < MAX_COLS - 1 && !is_wall_present(row, col, EAST_WALL)) {
//     flood_fill(row, col + 1); // East
//   }
//   if (row < MAX_ROWS - 1 && !is_wall_present(row, col, SOUTH_WALL)) {
//     flood_fill(row + 1, col); // South
//   }
//   if (col > 0 && !is_wall_present(row, col, WEST_WALL)) {
//     flood_fill(row, col - 1); // West
//   }
// }
//
// // Check if a wall is present in a specific direction
// bool is_wall_present(int row, int col, uint8_t wall_mask)
// {
//   return (maze[row][col] & wall_mask) != 0;
// }
//
// // Check if a cell is accessible in a specific direction
// bool is_cell_accessible(int row, int col, uint8_t access_mask)
// {
//   return (maze[row][col] & access_mask) != 0;
// }
//
// // Set accessibility for a cell
// void set_accessibility(int row, int col, uint8_t access_mask)
// {
//   if (is_valid_cell(row, col)) {
//     maze[row][col] |= access_mask;
//   }
// }
//
// // Check if the cell is part of the destination
// bool is_at_destination(int row, int col)
// {
//   return row >= destination_row && row < destination_row + dest_size &&
//          col >= destination_col && col < destination_col + dest_size;
// }

// void update_map(struct coordinate point, int orient, bool lwall, bool rwall,
// bool fwall);
//
// void floodFill(struct coordinate p, struct coordinate prev)
// {
//   if (!isConsistant(p)) {
//     flood[p.y][p.x] = flood[prev.y][prev.x] + 1;
//   }
//
//   std::queue<coordinate> q;
//   q.push(p);
//
//   struct surroundCoor surr = getSurrounds(p);
//   if (surr.N.x >= 0 && surr.N.y >= 0) {
//     if (isAccessible(p, surr.N)) {
//       q.push(surr.N);
//     }
//   }
//   if (surr.E.x >= 0 && surr.E.y >= 0) {
//     if (isAccessible(p, surr.E)) {
//       q.push(surr.E);
//     }
//   }
//   if (surr.S.x >= 0 && surr.S.y >= 0) {
//     if (isAccessible(p, surr.S)) {
//       q.push(surr.S);
//     }
//   }
//   if (surr.W.x >= 0 && surr.W.y >= 0) {
//     if (isAccessible(p, surr.W)) {
//       q.push(surr.W);
//     }
//   }
//
//   while (!q.empty()) {
//     struct coordinate crun = q.front();
//     q.pop();
//     if (isConsistant(crun)) {
//
//     } else {
//       makeConsistant(crun);
//       q.push(crun);
//       struct surroundCoor surr = getSurrounds(crun);
//       if (surr.N.y >= 0 && surr.N.x >= 0) {
//         if (isAccessible(crun, surr.N)) {
//           q.push(surr.N);
//         }
//       }
//       if (surr.E.y >= 0 && surr.E.x >= 0) {
//         if (isAccessible(crun, surr.E)) {
//           q.push(surr.E);
//         }
//       }
//       if (surr.S.y >= 0 && surr.S.x >= 0) {
//         if (isAccessible(crun, surr.S)) {
//           q.push(surr.S);
//         }
//       }
//       if (surr.W.y >= 0 && surr.W.x >= 0) {
//         if (isAccessible(crun, surr.W)) {
//           q.push(surr.W);
//         }
//       }
//     }
//   }
// }
//

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
