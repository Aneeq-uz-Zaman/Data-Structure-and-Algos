int firstNonRepeating(vector<int>& v) {
    vector<int> freq(2001, 0);  // index shift: +1000

    for (int x : v)
        freq[x + 1000]++;

    for (int x : v)
        if (freq[x + 1000] == 1)
            return x;

    return -1;
}