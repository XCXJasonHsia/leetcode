#include<vector>
#include<unordered_map>
#include<iostream>
#include<string>
#include<stack>
#include<set>
#include<algorithm>
#include<queue>
using namespace std;
/*
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int sum = nums[0], len = nums.size() + 1, start = 0, end = 0;
        while (end < nums.size()) {
            sum += nums[end];
            while (sum >= target) {
                len = min(len, end - start + 1);
                sum -= nums[start++];
            }
            end++;
        }
        if (len == nums.size() + 1)
            return 0;
        else
            return len;
    }
};
*/

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size(), aim = 0, len = nums.size() + 1;
        vector<int> sums(n + 1, 0);
        for (int i = 1; i < n + 1; i++) {
            sums[i] = sums[i - 1] + nums[i - 1];
        }
        for (int i = 1; i < n + 1; i++) {
            aim = target + sums[i - 1];
            int pos = binarySearch(sums, 0, n, aim);
            if (pos != -1) {
                len = min(len, pos - i + 1);
            }
        }
        if (len == n + 1)
            return 0;
        else
            return len;
    }

    int binarySearch(const vector<int>& sums, int start, int end, int target) {
        int mid = 0;
        while (start < end) {
            mid = (start + end) / 2;
            if (sums[mid] == target)
                return mid;
            else if (sums[mid] < target) {
                start = mid + 1;
            }
            else {
                end = mid;
            }
        }
        return sums[start] >= target ? start : -1;
    }
};

int main() {
    Solution test;
    vector<int> inputArr = {2, 3, 1, 2, 4, 3};
    cout << test.minSubArrayLen(7, inputArr)<<endl;
}