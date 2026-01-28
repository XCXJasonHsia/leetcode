#include<vector>
#include<unordered_map>
#include<iostream>
#include<string>
#include<set>
#include<algorithm>
#include<queue>
using namespace std;


class Convert {
public:
    size_t operator()(const int& y, const int& x) const {
        return (static_cast<size_t>(static_cast<unsigned int>(y)) << 32) ^
            static_cast<size_t>(static_cast<unsigned int>(x));
    }
    size_t operator()(const pair<int, int>& p) const {
        return (static_cast<size_t>(static_cast<unsigned int>(p.first)) << 32) ^
            static_cast<size_t>(static_cast<unsigned int>(p.second));
    }
}convert;

bool find_in_stack(stack<pair<int, int>> Stack, const pair<int, int>& el) {
    //cout << "find " << "(" << el.first << ", " << el.second << ")" << " : ";
    while (!Stack.empty()) {
        if (el == Stack.top())
        {
            //cout << "true\n";
            return true;
        }
        Stack.pop();
    }
    //cout << "false\n";
    return false;
}

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        n = grid.size();
        vector<vector<pair<int, int>>> label(n,
            vector<pair<int, int>>(n, unvisited));
        Label = label;
        //DFS
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (Label[i][j] != unvisited) continue;
                else if (grid[i][j] == 1) {
                    islandArea[convert(i, j)] = 1;
                    Label[i][j] = pair<int, int>(i, j);
                    pushStack(pair<int, int>(i, j));
                    while (!toBeVisited.empty()) {
                        pair<int, int> current = toBeVisited.top();
                        int y = current.first, x = current.second;
                        toBeVisited.pop();
                        //showStack(toBeVisited);
                        if (grid[y][x]) {
                            pushStack(pair<int, int>(y, x));
                            Label[y][x] = pair<int, int>(i, j);
                            islandArea[convert(i, j)]++;
                        }
                        else
                            Label[y][x] = pair<int, int>(y, x);
                    }
                }
                else
                    Label[i][j] = pair<int, int>(i, j);
            }
        }
        //showHash();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (grid[i][j] == 0)
                    mergeIsland(pair<int, int>(i, j));
        if (maxArea == 0)
            maxArea = n * n;
        return maxArea;
    }
private:
    void pushStack(pair<int, int> spot) {
        int y = spot.first, x = spot.second;
        if (y > 0 && Label[y - 1][x] == unvisited &&
            !find_in_stack(toBeVisited, pair<int, int>(y - 1, x)))
            toBeVisited.push(pair<int, int>(y - 1, x));
        if (y < n - 1 && Label[y + 1][x] == unvisited && 
            !find_in_stack(toBeVisited, pair<int, int>(y + 1, x)))
            toBeVisited.push(pair<int, int>(y + 1, x));
        if (x > 0 && Label[y][x - 1] == unvisited && 
            !find_in_stack(toBeVisited, pair<int, int>(y, x - 1)))
            toBeVisited.push(pair<int, int>(y, x - 1));
        if (x < n - 1 && Label[y][x + 1] == unvisited && 
            !find_in_stack(toBeVisited, pair<int, int>(y, x + 1)))
            toBeVisited.push(pair<int, int>(y, x + 1));
        //showStack(toBeVisited);
    }
    void mergeIsland(pair<int, int> spot) {
        int y = spot.first, x = spot.second, area = 1;
        unordered_map<size_t, int> islandArea1(islandArea);
        if (y > 0 && islandArea1.count(convert(Label[y - 1][x]))) {
            area += islandArea1[convert(Label[y - 1][x])];
            islandArea1.erase(convert(Label[y - 1][x]));
        }
        if (y < n - 1 && islandArea1.count(convert(Label[y + 1][x]))) {
            area += islandArea1[convert(Label[y + 1][x])];
            islandArea1.erase(convert(Label[y + 1][x]));
        }
        if (x > 0 && islandArea1.count(convert(Label[y][x - 1]))) {
            area += islandArea1[convert(Label[y][x - 1])];
            islandArea1.erase(convert(Label[y][x - 1]));
        }
        if (x < n - 1 && islandArea1.count(convert(Label[y][x + 1]))) {
            area += islandArea1[convert(Label[y][x + 1])];
            islandArea1.erase(convert(Label[y][x + 1]));
        }
        if (maxArea < area) maxArea = area;
    }
    
    void showHash() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (islandArea.count(convert(i, j)))
                    cout << convert(i, j) << " (" << i << ", " << j << ") -> " << islandArea[convert(i, j)] << endl;
                if (convert(i, j) == convert(pair<int, int>(i, j)))
                    cout << "correct" << endl;
            }
        }
    }
    
    void showStack(stack<pair<int, int>> Stack) {
        cout << "\n\ntobevisited:\n";
        while (!Stack.empty()) {
            pair<int, int> tmp = Stack.top();
            cout << "(" << tmp.first << ", " << tmp.second << ")" << endl;
            Stack.pop();
        }
    }

    const pair<int, int> unvisited = {-1, -1};
    int n;
    vector<vector<pair<int, int>>> Label;
    unordered_map<size_t, int> islandArea;
    stack<pair<int, int>> toBeVisited;
    int maxArea = 0;
};

int main() {
    vector<vector<int>> grid = { {1, 0, 0, 1, 1}, 
                                 {1, 0, 0, 1, 0},
                                 {1, 1, 1, 1, 1},
                                 {1, 1, 1, 0, 1},
                                 {0, 0, 0, 1, 0},
                                };
    Solution test;
    cout << test.largestIsland(grid) << endl;
}