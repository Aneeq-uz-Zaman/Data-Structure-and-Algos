// BFS-based maze solver using Queue (finds shortest path)
// This version uses a queue to implement Breadth-First Search which guarantees the shortest path

#include <iostream>
#include "queue.h"
using namespace std;

const int ROWS = 6;
const int COLS = 6;

struct Position {
    int row, col;
    Position(int r = 0, int c = 0) : row(r), col(c) {}
};

bool solve_maze_bfs(char maze[6][6], Position start, Position target) {
    CircularQueue<Position> queue(36);
    bool visited[ROWS][COLS] = {false};
    Position parent[ROWS][COLS];
    
    // Initialize parent matrix
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            parent[i][j] = Position(-1, -1);
        }
    }
    
    queue.enqueue(start);
    visited[start.row][start.col] = true;
    
    // Direction vectors: down, right, up, left
    int directions[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};
    
    while (!queue.isEmpty()) {
        Position current = queue.dequeue();
        
        // Check if we reached the target
        if (current.row == target.row && current.col == target.col) {
            // Reconstruct and print path
            cout << "Shortest path found using BFS:" << endl;
            
            // Build path backwards from target to start
            Position path[36];
            int pathLength = 0;
            Position temp = target;
            
            while (!(temp.row == start.row && temp.col == start.col)) {
                path[pathLength++] = temp;
                temp = parent[temp.row][temp.col];
            }
            path[pathLength++] = start;
            
            // Print path from start to target
            cout << "Path: ";
            for (int i = pathLength - 1; i >= 0; i--) {
                cout << "(" << path[i].row << "," << path[i].col << ")";
                if (i > 0) cout << " -> ";
            }
            cout << endl;
            cout << "Path length: " << pathLength << " steps" << endl;
            return true;
        }
        
        // Explore all four directions
        for (int i = 0; i < 4; i++) {
            int new_r = current.row + directions[i][0];
            int new_c = current.col + directions[i][1];
            
            // Check bounds and if cell is valid and not visited
            if (new_r >= 0 && new_r < ROWS && new_c >= 0 && new_c < COLS && 
                !visited[new_r][new_c]) {
                
                // Check if the cell is traversable (space, P, or T)
                if (maze[new_r][new_c] == ' ' || maze[new_r][new_c] == 'P' || maze[new_r][new_c] == 'T') {
                    visited[new_r][new_c] = true;
                    parent[new_r][new_c] = current;
                    queue.enqueue(Position(new_r, new_c));
                }
            }
        }
    }
    
    cout << "No path found using BFS!" << endl;
    return false;
}

void print_maze(char maze[6][6]) {
    cout << "Maze:" << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    char maze[6][6] = {
        {' ', '*', ' ', '*', ' ', ' '},
        {' ', '*', ' ', '*', ' ', ' '},
        {'P', ' ', ' ', ' ', '*', ' '},
        {'*', ' ', '*', '*', '*', ' '},
        {' ', ' ', ' ', ' ', '*', 'T'},
        {'*', ' ', ' ', ' ', ' ', ' '}
    };

    // Find P and T positions
    Position start, target;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == 'P') {
                start = Position(i, j);
            }
            if (maze[i][j] == 'T') {
                target = Position(i, j);
            }
        }
    }

    print_maze(maze);
    cout << "Starting position P: (" << start.row << "," << start.col << ")" << endl;
    cout << "Target position T: (" << target.row << "," << target.col << ")" << endl;
    cout << endl;

    if (solve_maze_bfs(maze, start, target)) {
        cout << "Maze solved using BFS!" << endl;
    } else {
        cout << "Maze unsolved!" << endl;
    }

    return 0;
}