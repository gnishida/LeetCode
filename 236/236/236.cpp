#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		vector<vector<TreeNode*>> S(3);

		return dfs(root, p, q, S);
	}

private:
	TreeNode* dfs(TreeNode* root, TreeNode* p, TreeNode* q, vector<vector<TreeNode*>>& S) {
		S[0].push_back(root);

		if (root == p) {
			// Found p
			S[1] = S[0];
		} else if (root == q) {
			// Found q
			S[2] = S[0];
		}

		// Found both p and q, so find the LCA
		if (S[1].size() > 0 && S[2].size() > 0) {
			int n = min(S[1].size(), S[2].size());
			for (int i = 0; i < n; i++) {
				if (S[1][i] != S[2][i]) return S[1][i - 1];
			}
			return S[1][n - 1];
		}

		if (root->left) {
			TreeNode* ret = dfs(root->left, p, q, S);
			if (ret) return ret;
		}
		if (root->right) {
			TreeNode* ret = dfs(root->right, p, q, S);
			if (ret) return ret;
		}
		S[0].pop_back();
		return nullptr;
	}
};

int main() {
	TreeNode* root = new TreeNode(3);
	root->left = new TreeNode(5);
	root->left->left = new TreeNode(6);
	root->left->right = new TreeNode(2);
	root->left->right->left = new TreeNode(7);
	root->left->right->right = new TreeNode(4);
	root->right = new TreeNode(1);
	root->right->left = new TreeNode(0);
	root->right->right = new TreeNode(8);

	Solution sol;
	cout << sol.lowestCommonAncestor(root, root->left, root->right)->val << endl;
	cout << sol.lowestCommonAncestor(root, root->left, root->left->right->right)->val << endl;

	return 0;
}