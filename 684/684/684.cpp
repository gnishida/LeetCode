#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	vector<int> findRedundantConnection(vector<vector<int>>& edges) {
		return kruskal(edges.size(), edges);
	}

private:
	int kruskal_getRoot(vector<int>& parents, int u) {
		if (parents[u] == -1) return u;

		int root = kruskal_getRoot(parents, parents[u]);
		parents[u] = root;
		return root;
	}

	void kruskal_merge(vector<int>& parents, int u, int v) {
		int root_u = kruskal_getRoot(parents, u);
		int root_v = kruskal_getRoot(parents, v);

		if (root_u != root_v) {
			parents[root_v] = root_u;
		}
	}

	// edges contain edge <weight, <u, v>>
	vector<int> kruskal(int N, vector<vector<int>>& edges) {
		vector<int> parents(N, -1);
		for (const auto& edge : edges) {
			const auto& u = edge[0];
			const auto& v = edge[1];

			int root_u = kruskal_getRoot(parents, u);
			int root_v = kruskal_getRoot(parents, v);
			if (root_u == root_v) return { u, v };

			kruskal_merge(parents, u, v);
		}

		return { 0, 0 };
	}

};

int main() {
	vector<vector<int>> edges = {
		{1, 2}, {1, 3}, {2, 3}
	};

	Solution sol;
	auto ans = sol.findRedundantConnection(edges);
	cout << "[" << ans[0] << "," << ans[1] << "]" << endl;

	return 0;
}