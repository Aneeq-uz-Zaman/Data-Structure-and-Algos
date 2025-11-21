#include <iostream>
using namespace std;

int countSquares(int k, int x, int y)
{
    int cx = 1024, cy = 1024;
    int r = 0;
    if (k < 1){
        return 0;
    }


    // can't undertand the question properly :)



    return r;
}

int main() {
    int k, x, y;
    cin >> k >> x >> y;

    int result = countSquares(k, x, y);
    cout << result << endl;

    return 0;
}
