using namespace std;
#include <iostream>
#include "Stack.h"
struct Pair
{
    int i;
    int j;
};

void solve_maze(char maze[6][6], Pair s, Pair d, int row, int col)
{
    Stack<Pair> a;
    a.push(s);
    maze[s.i][s.j] = '5';  

    
    while (s.i != d.i || s.j != d.j)
    {
        
        if (s.j + 1 < col && maze[s.i][s.j + 1] != '*' && maze[s.i][s.j + 1] != '5')
        {
            s.j++;
            maze[s.i][s.j] = '5';
            a.push(s);
        }
      
        else if (s.i + 1 < row && maze[s.i + 1][s.j] != '*' && maze[s.i + 1][s.j] != '5')
        {
            s.i++;
            maze[s.i][s.j] = '5';
            a.push(s);
        }
       
        else if (s.i - 1 >= 0 && maze[s.i - 1][s.j] != '*' && maze[s.i - 1][s.j] != '5')
        {
            s.i--;
            maze[s.i][s.j] = '5';
            a.push(s);
        }
       
        else if (s.j - 1 >= 0 && maze[s.i][s.j - 1] != '*' && maze[s.i][s.j - 1] != '5')
        {
            s.j--;
            maze[s.i][s.j] = '5';
            a.push(s);
        }
      
        else
        {
            if (a.empty()) break;  
            Pair f = a.pop();
            s.i = f.i;
            s.j = f.j;
        }
    }

    if (s.i == d.i && s.j == d.j)
    {
        cout << "FOUND ";
       
        if (a.empty() || a.top().i != d.i || a.top().j != d.j) a.push(d);

        while (!a.empty())
        {
            Pair cd = a.pop();
            cout << "(" << cd.i << "," << cd.j << ") ";
        }
    }
    else
    {
        cout << "NOT FOUND ";
    }
}

// Helper: print the maze
void print_maze(char maze[6][6], int row, int col)
{
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
            cout << maze[i][j] << ' ';
        cout << endl;
    }
}

// Main: demo and usage instructions
// Usage (Windows):
//  - With MinGW: g++ -std=c++11 "d:\\C++\\DSA\\lab-04(QUEUE)\\shah-maze.cpp" -o "d:\\C++\\DSA\\lab-04(QUEUE)\\shah-maze.exe"
//  - Run: d:\\C++\\DSA\\lab-04(QUEUE)\\shah-maze.exe
// This main provides a small 6x6 example maze. Walls are '*' and open cells are '.'. Visited
// path cells are marked with '5' by the solver.
int main()
{
    const int R = 6, C = 6;
    char maze[R][C] = {
        {'.','*','.','.','.','.'},
        {'.','*','.','*','*','.'},
        {'.','.','.','.','.','.'},
        {'*','*','*','*','.','*'},
        {'.','.','.','.','.','.'},
        {'.','*','*','*','.','.'}
    };

    cout << "Maze solver demo (6x6)\n";
    cout << "Legend: '*' = wall, '.' = free cell, '5' = visited path" << endl << endl;

    cout << "Initial maze:\n";
    print_maze(maze, R, C);

    // Example start and destination
    Pair start{0, 0};
    Pair dest{4, 5};

    cout << "\nSolving from (" << start.i << "," << start.j << ") to (" << dest.i << "," << dest.j << ")...\n";
    solve_maze(maze, start, dest, R, C);

    cout << "\nMaze after solver (visited cells marked '5'):\n";
    print_maze(maze, R, C);

    cout << "\nDone.\n";
    return 0;
}