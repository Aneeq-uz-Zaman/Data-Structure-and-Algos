#include <iostream>
#include "Stack.h"
using namespace std;

const int ROWS = 6;
const int COLS = 6;

int main() {
    
    char maze[6][6] = {
    {' ', '*', ' ', '*', ' ', ' '},
    {' ', '*', ' ', '*', ' ', ' '},
    {'P', ' ', ' ', ' ', '*', ' '},
    {'*', ' ', '*', '*', '*', ' '},
    {' ', ' ', ' ', ' ', '*', 'T'},
    {'*', ' ', ' ', ' ', ' ', ' '}
    };


    int sr = 1, sc = 0;   
    int er = 3, ec = 5;   

    
    bool visited[ROWS][COLS] = {false};

    int r = sr, c = sc;

    cout << "Path: (" << r << "," << c << ") ";

    while (!(r == er && c == ec)) {
        visited[r][c] = true;


        if (r+1 < ROWS && maze[r+1][c] == ' ' && !visited[r+1][c]) {
            r++;
            
        }
        else if (c+1 < COLS && maze[r][c+1] == ' ' && !visited[r][c+1]) {

            c++;
            
        }

        else if (c-1 >= 0 && maze[r][c-1] == ' ' && !visited[r][c-1]) {

            c--;
        }
        else if (r-1 >= 0 && maze[r-1][c] == ' ' && !visited[r-1][c]) {

            r--;
            
        }
        else{
            cout<<"not found";
            return 0;
        }
        cout << "-> (" << r << "," << c << ") ";
    }

    cout << "\nReached destination (" << er << "," << ec << ")!\n";
    return 0;
}
