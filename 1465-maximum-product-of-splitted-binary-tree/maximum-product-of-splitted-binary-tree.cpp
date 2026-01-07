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
class Solution {
public:
    long long totalSum = 0;
    long long ans = 0;
    const int MOD = 1e9 + 7;

    // DFS to compute total sum
    long long computeTotal(TreeNode* root) {
        if (!root) return 0;
        return root->val + computeTotal(root->left) + computeTotal(root->right);
    }

    // DFS to compute subtree sums and max product
    long long dfs(TreeNode* root) {
        if (!root) return 0;

        long long left = dfs(root->left);
        long long right = dfs(root->right);

        long long subSum = root->val + left + right;

        // product if we cut above this subtree
        ans = max(ans, subSum * (totalSum - subSum));

        return subSum;
    }

    int maxProduct(TreeNode* root) {
        totalSum = computeTotal(root);
        dfs(root);
        return ans % MOD;
    }
};
