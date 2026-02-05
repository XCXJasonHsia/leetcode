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
    bool isCode(const char& ch) {
        if (ch == '0')
            return false;
        return true;
    }
    bool isCode(const string& str) {
        int code = (str[0] - '0') * 10 + (str[1] - '0');
        if (code >= 10 && code <= 26)
            return true;
        return false;
    }
    int numDecodings(string s) {
        int len = s.size(), i = 2;
        if (s.size() == 0)
            return 0;
        vector<int> dp(s.size(), 0);
        if (isCode(s[0]))
            dp[0] = 1;
        if (s.size() == 1)
            return dp[0];
        if (isCode(s.substr(0, 2))) {
            if (isCode(s[1]))
                dp[1] = 1 + dp[0];
            else
                dp[1] = 1;
        }
        else if (isCode(s[1])) {
            dp[1] = dp[0];
        }
        while (i < len) {
            if (isCode(s.substr(i - 1, 2))) {
                if (isCode(s[i]))
                    dp[i] = dp[i - 2] + dp[i - 1];
                else
                    dp[i] = dp[i - 2];
            }
            else if (isCode(s[i])) {
                dp[i] = dp[i - 1];
            }
            i++;
        }
        return dp[len - 1];
    }
};

int main() {
    string s = "2101";
    Solution test;
    cout << test.numDecodings(s) << endl;
}