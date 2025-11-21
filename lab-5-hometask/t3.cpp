#include <iostream>
using namespace std;

string reverse(string s, int len) {
    if (len == 0)
        return "";
    return s[len - 1] + reverse(s, len - 1);
}

int main() {
    string s;
    cin >> s;
    cout << reverse(s, s.length());
    return 0;
}
