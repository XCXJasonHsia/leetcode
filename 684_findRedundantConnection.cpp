#include<vector>
#include<unordered_map>
#include<iostream>
#include<string>
#include<set>
#include<algorithm>
#include<queue>
using namespace std;

class Solution {
public:
    int findRoot(vector<int>& parent, int i) const {
        while (parent[i] != i)
            i = parent[i];
        return i;
    }
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> parent(edges.size() + 1, 0), result;
        for (int i = 1; i <= edges.size(); i++)
            parent[i] = i;
        for (int i = 0; i < edges.size(); i++) {
            int root1 = findRoot(parent, edges[i][0]),
                root2 = findRoot(parent, edges[i][1]);
            if (root1 == root2)
                return edges[i];
            else
                parent[root2] = root1;
        }
        return result;
    }
    
};

int main() {
    vector<vector<int>> edges = { {1, 2}, {2, 3}, {1, 3} };
    Solution test;
    vector<int> result = test.findRedundantConnection(edges);
    cout << result[0] << result[1] << endl;
}