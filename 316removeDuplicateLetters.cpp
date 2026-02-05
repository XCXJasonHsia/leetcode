#include<vector>
#include<unordered_map>
#include<iostream>
#include<string>
#include<stack>
#include<set>
#include<algorithm>
#include<queue>
using namespace std;

class Solution {
public:
    void reverse(string& s) {
        char tmp;
        int i = 0, j = s.size() - 1;
        while (i < j) {
            tmp = s[i];
            s[i] = s[j];
            s[j] = tmp;
            i++;
            j--;
        }
    }

    string removeDuplicateLetters(string s) {
        int ks[26] = { 0 };
        string st;
        set<char> seen;
        for (int i = 0; i < s.size(); i++) {
            ks[s[i] - 'a']++;
        }
        for (int i = 0; i < s.size(); i++) {
            if (!seen.count(s[i])) {
                while (st.size() && s[i] < st.back() &&
                    ks[st.back() - 'a']) {
                    seen.erase(st.back());
                    st.pop_back();
                }
                st.push_back(s[i]);
                seen.insert(s[i]);
            }
            ks[s[i] - 'a']--;
        }
        return st;
    }
};

int main() {
    string s = "cdadabcc";
    Solution test;
    cout << test.removeDuplicateLetters(s) << endl;
}