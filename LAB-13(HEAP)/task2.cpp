#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;
int firstNonRepeating(vector<int>& v) {
    vector<int> freq(2001, 0);  

    for (int i=0;i<v.size();i++)
    {
        int r=v[i]+1000;
        freq[r]++;
    }
    for (int j=0;j<v.size();j++)
    {
        if (freq[v[j]+1000] == 1)
            return v[j];
    }
    return -1;
}

int main()
{
    vector<int> v={4, 5, 6, 7, 4, 6, 5, 6, 4, 5, 5, 6,7,-9};
    cout<<firstNonRepeating(v);

    
    
    return 0;
}