#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
void Frequency(string st) {
	vector<pair<int,string>> freq;
	freq.resize(26);

	for(int i=0; i<st.length();i++){
		freq[i].first=0;
	}
	for(int i=0; i<st.length(); i++) {
		int index=st[i]-65;
		freq[index].second+=st[i];
		freq[index].first++;
	}
	sort(freq.begin(), freq.end(),
        [](auto& a, auto& b) {
            if (a.second == b.second)
                return a.first < b.first;
            return a.second < b.second;
        });
    
	for(int i=0; i<freq.size(); i++) {
		if(freq[i].first==0) {
			continue;
		}
		cout<<freq[i].second;
	}
}
int main() {
	string st="XZXYYZZYYXYYZZZWWQQQQQVVVVVVVVVWXX ";
	Frequency(st);
	return 0;
}