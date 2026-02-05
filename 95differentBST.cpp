#include<vector>
#include<unordered_map>
#include<iostream>
#include<string>
#include<stack>
#include<set>
#include<algorithm>
#include<queue>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct TreeNode {
    int val;
    TreeNode* left, * right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x)
        , left(left), right(right) {}
};
/*
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> result;
        result.push_back(new TreeNode(1));
        for (int i = 2; i <= n; i++) {
            insertNumber(result, i);
        }
        showTrees(result);
        return result;
    }
private:
    void insertNumber(vector<TreeNode*>& roots, const int& n) {
        int size = roots.size();
        for (int i = 0; i < size; i++) {
            TreeNode* tmp = roots[i], * prev = roots[i], * newLeaf = new TreeNode(n);
            TreeNode* newTree = new TreeNode(n, copy(roots[i]), nullptr);
            roots.push_back(newTree);
            //showTrees(roots);
            while (tmp->right) {
                prev = tmp;
                tmp = tmp->right;
                prev->right = newLeaf;
                newLeaf->left = tmp;
                roots.push_back(copy(roots[i]));
                //showTrees(roots);
                prev->right = tmp;
            }
            newLeaf->left = 0;
            tmp->right = newLeaf;
            //showTrees(roots);
        }
    }
    void showTrees(vector<TreeNode*>& roots) {
        cout << "trees\n";
        for (int i = 0; i < roots.size(); i++) {
            showTree(roots[i]);
            cout << "\n\n";
        }
    }
    void showTree(TreeNode* root) {
        if (root == 0) return;
        cout << root->val << "  ";
        if (root->left) showTree(root->left);
        else cout << "0  ";
        if (root->right) showTree(root->right);
        else cout << "0  ";
    }
    TreeNode* copy(TreeNode* root) {
        if (root == 0) return nullptr;
        return new TreeNode(root->val, copy(root->left), copy(root->right));
    }
};
*/

class Solution {
public:
    vector<TreeNode*> generateTrees(int start, int end) {
        if (start >= end)
            return { nullptr };
        vector<TreeNode*> result;
        for (int i = start + 1; i <= end; i++) {
            vector<TreeNode*> leftTrees = generateTrees(start, i - 1);
            vector<TreeNode*> rightTrees = generateTrees(i, end);
            for (auto& left : leftTrees) {
                for (auto& right : rightTrees) {
                    result.emplace_back(new TreeNode(i, left, right));
                }
            }
        }
        //showTrees(result);
        return result;
    }
    vector<TreeNode*> generateTrees(int n) {
        return generateTrees(0, n);
    }
    void showTrees(vector<TreeNode*>& roots) {
        cout << "trees\n";
        for (int i = 0; i < roots.size(); i++) {
            showTree(roots[i]);
            cout << "\n\n";
        }
    }
    void showTree(TreeNode* root) {
        if (root == 0) return;
        cout << root->val << "  ";
        if (root->left) showTree(root->left);
        else cout << "0  ";
        if (root->right) showTree(root->right);
        else cout << "0  ";
    }
};

int main() {
    Solution test;
    test.generateTrees(7);
}