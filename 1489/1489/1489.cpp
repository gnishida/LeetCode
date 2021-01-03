#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
	vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
		for (int i = 0; i < edges.size(); i++) {
			edges[i].push_back(i);
		}

		// Sort the edges
		sort(edges.begin(), edges.end(), [](const auto& v1, const auto& v2) {
			return v1[2] < v2[2];
		});

		int best = kruskal(n, edges, -1, -1);

		vector<vector<int>> ans(2);
		for (int i = 0; i < edges.size(); i++) {
			// Run kruskal excluding this edge
			if (kruskal(n, edges, i, -1) > best) {
				ans[0].push_back(edges[i][3]);
			} else {
				// Run kruskal using this edge
				if (kruskal(n, edges, -1, i) == best) {
					ans[1].push_back(edges[i][3]);
				}
			}
		}

		return ans;
	}

private:
	int kruskal(int n, const vector<vector<int>>& edges, int removedEdgeIndex, int initialUseEdgeIndex) {
		vector<int> parents(n);
		for (int i = 0; i < n; i++) {
			parents[i] = i;
		}

		int numGroups = n;
		int mstSize = 0;

		if (initialUseEdgeIndex >= 0) {
			const int& u = edges[initialUseEdgeIndex][0];
			const int& v = edges[initialUseEdgeIndex][1];
			const int& d = edges[initialUseEdgeIndex][2];

			mstSize += d;
			merge(parents, u, v);
			numGroups--;
		}

		for (int i = 0; i < edges.size(); i++) {
			if (i == removedEdgeIndex || i == initialUseEdgeIndex) continue;

			const int& u = edges[i][0];
			const int& v = edges[i][1];
			const int& d = edges[i][2];

			int root_u = getRoot(parents, u);
			int root_v = getRoot(parents, v);
			if (root_u == root_v) continue;

			mstSize += d;

			// Merge root_u and root_v
			merge(parents, root_u, root_v);
			numGroups--;
		}

		if (numGroups == 1) {
			return mstSize;
		} else {
			return numeric_limits<int>::max();
		}
	}

	void merge(vector<int>& parents, int root_u, int root_v) {
		parents[root_v] = root_u;
	}

	int getRoot(vector<int>& parents, int u) {
		int root = u;
		while (parents[u] != u) {
			root = getRoot(parents, parents[u]);
			parents[u] = root;
			u = root;
		}

		return root;
	}
};

int main() {
	vector<vector<int>> edges = {
		{0,1,1}, {1, 2, 1}, {0, 2, 1}, {2, 3, 4}, {3, 4, 2}, {3, 5, 2}, {4, 5, 2}
	};
	Solution sol;
	vector<vector<int>> results = sol.findCriticalAndPseudoCriticalEdges(6, edges);
	cout << "[";
	for (int i = 0; i < results.size(); i++) {
		if (i > 0) cout << ",";
		cout << "[";
		for (int j = 0; j < results[i].size(); j++) {
			if (j > 0) cout << ",";
			cout << results[i][j];
		}
		cout << "]";
	}
	cout << "]";

	return 0;
}