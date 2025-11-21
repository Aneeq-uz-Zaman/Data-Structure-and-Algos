// The maze is represented by a 2D array of characters, the character * marks a barrier, and P and T mark the parking lot
// and mountain top, respectively. A blank space marks a step along a path. Your program then attempts to find a path
// through the maze and returns "solved" or "unsolved" depending on the outcome and if the maze is solved it should print
// the complete path.

#include <iostream>
#include "Stack.h"
using namespace std;

const int ROWS = 6;
const int COLS = 6;

struct Position {
    int row, col;
    Position(int r = 0, int c = 0) : row(r), col(c) {}
};

bool solve_maze(char maze[6][6], Position start, Position target) {
    Stack<Position> path(36);
    bool visited[ROWS][COLS] = {false};
    
    path.push(start);
    
    while (!path.empty()) {
        Position current = path.top();
        int r = current.row;
        int c = current.col;
        
        // Check if we reached the target
        if (r == target.row && c == target.col) {
            cout << "Path found: ";
            Stack<Position> temp_path(36);
            
            // Print path from start to end
            while (!path.empty()) {
                temp_path.push(path.pop());
            }
            while (!temp_path.empty()) {
                Position pos = temp_path.pop();
                cout << "(" << pos.row << "," << pos.col << ")";
                if (!temp_path.empty()) cout << " -> ";
            }
            cout << endl;
            return true;
        }
        
        visited[r][c] = true;
        bool found_move = false;
        
        // Try all four directions: down, right, left, up
        int directions[4][2] = {{1,0}, {0,1}, {0,-1}, {-1,0}};
        
        for (int i = 0; i < 4; i++) {
            int new_r = r + directions[i][0];
            int new_c = c + directions[i][1];
            
            // Check bounds
            if (new_r >= 0 && new_r < ROWS && new_c >= 0 && new_c < COLS && !visited[new_r][new_c]) {
                // Check if the cell is traversable (space, P, or T)
                if (maze[new_r][new_c] == ' ' || maze[new_r][new_c] == 'P' || maze[new_r][new_c] == 'T') {
                    path.push(Position(new_r, new_c));
                    found_move = true;
                    break;
                }
            }
        }
        
        // If no valid move found, backtrack
        if (!found_move) {
            path.pop();
        }
    }
    
    cout << "No path found!" << endl;
    return false;
}

int main() {
    char maze[6][6] = {
    {' ', '*', ' ', '*', ' ', 'T'},
    {' ', '*', ' ', '*', ' ', ' '},
    {'P', ' ', ' ', ' ', '*', ' '},
    {'*', ' ', '*', '*', '*', ' '},
    {' ', ' ', ' ', ' ', '*', ' '},
    {'*', ' ', ' ', ' ', ' ', ' '}
    };

    // Find P and T positions
    Position start, target;
    start = Position(2, 0); // P position
    target = Position(0, 5); // T position

    cout << "Starting position P: (" << start.row << "," << start.col << ")" << endl;
    cout << "Target position T: (" << target.row << "," << target.col << ")" << endl;
    cout << endl;

    if (solve_maze(maze, start, target)) {
        cout << "Maze solved!" << endl;
    } else {
        cout << "Maze unsolved!" << endl;
    }

    return 0;
}
