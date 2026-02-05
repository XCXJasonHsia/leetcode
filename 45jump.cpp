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
    int jump(vector<int>& nums) {
        int boundary = 0, prevBoundary = 0, i = 0, steps = 0;
        while (boundary < nums.size() - 1) {
            for (; i <= prevBoundary; i++) {
                if (i + nums[i] > boundary)
                    boundary = i + nums[i];
            }
            prevBoundary = boundary;
            steps++;
        }
        return steps;
    }
};