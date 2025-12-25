string sortByFrequency(string s) {
    vector<pair<int, int>> freq(26);

    for (int i = 0; i < 26; i++)
        freq[i] = {i, 0};

    for (char c : s)
        freq[c - 'A'].second++;

    sort(freq.begin(), freq.end(),
        [](auto& a, auto& b) {
            if (a.second == b.second)
                return a.first < b.first;
            return a.second < b.second;
        });

    string result = "";
    for (auto& p : freq)
        result.append(p.second, char(p.first + 'A'));

    return result;
}