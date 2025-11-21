#include <iostream>
using namespace std;

const int ROWS = 3;
const int COLS = 4;

int main() {
    
    char maze[ROWS][COLS] = {
        {'*','.','*','*'},
        {'.','.','.','*'},
        {'*','*','.','.'},
    };

    int sr = 0, sc = 1;   
    int er = 2, ec = 3;   

    
    bool visited[ROWS][COLS] = {false};

    int r = sr, c = sc;

    cout << "Path: (" << r << "," << c << ") ";

    while (!(r == er && c == ec)) {
        visited[r][c] = true;


        if (r+1 < ROWS && maze[r+1][c] == '.' && !visited[r+1][c]) {
            r++;
        }
        else if (c+1 < COLS && maze[r][c+1] == '.' && !visited[r][c+1]) {
            c++;
        }

        else if (c-1 >= 0 && maze[r][c-1] == '.' && !visited[r][c-1]) {
            c--;
        }
        else if (r-1 >= 0 && maze[r-1][c] == '.' && !visited[r-1][c]) {
            r--;
        }
        else {
            cout << "\nNo path found!\n";
            return 0;
        }

        cout << "-> (" << r << "," << c << ") ";
    }

    cout << "\nReached destination (" << er << "," << ec << ")!\n";
    return 0;
}

// Core Idea

// We are trying to get from a start cell to an end cell in a grid (maze).

// We use a stack to keep track of the cells we can explore next.

// At each step, we take the top of the stack (LIFO = last in, first out).

// We mark it as visited.

// If it is the goal, we stop.

// Otherwise, we push its valid neighbors (up, down, left, right) into the stack.

// We also maintain a parent array so we can reconstruct the path backward when we find the goal.