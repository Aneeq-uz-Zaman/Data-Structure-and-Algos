#include <iostream>
using namespace std;

#define N 5

bool findPath(char maze[N][N], int x, int y, bool visited[N][N]) {
    // Check boundaries and obstacles
    if (x < 0 || y < 0 || x >= N || y >= N || maze[x][y] == '1' || visited[x][y])
        return false;

    // If destination found
    if (maze[x][y] == 'D') {
        cout << "(" << x << "," << y << ") ";
        return true;
    }

    visited[x][y] = true; // mark current cell

    // Move Down
    if (findPath(maze, x + 1, y, visited)) {
        cout << "(" << x << "," << y << ") ";
        return true;
    }
    // Move Right
    if (findPath(maze, x, y + 1, visited)) {
        cout << "(" << x << "," << y << ") ";
        return true;
    }
    // Move Up
    if (findPath(maze, x - 1, y, visited)) {
        cout << "(" << x << "," << y << ") ";
        return true;
    }
    // Move Left
    if (findPath(maze, x, y - 1, visited)) {
        cout << "(" << x << "," << y << ") ";
        return true;
    }

    visited[x][y] = false; // backtrack
    return false;
}

int main() {
    char maze[N][N] = {
        {'S', '0', '1', '0', '0'},
        {'1', '0', '1', '0', '1'},
        {'0', '0', '0', '0', '0'},
        {'1', '0', '1', '0', '1'},
        {'0', '0', '0', 'D', '1'}
    };

    bool visited[N][N] = {false};

    int startX = 0, startY = 0; // position of 'S'

    if (!findPath(maze, startX, startY, visited))
        cout << "No path found!";
    else
        cout << "\nPath found above (in reverse order).";

    return 0;
}
