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
		// Sort the edges
		vector<pair<int, int>> orderedEdges;
		for (int i = 0; i < edges.size(); i++) {
			const auto& d = edges[i][2];
			orderedEdges.push_back({ d, i });
		}
		sort(orderedEdges.begin(), orderedEdges.end());

		int best = kruskal(n, edges, orderedEdges, -1, -1);

		vector<vector<int>> ans(2);
		for (int i = 0; i < edges.size(); i++) {
			vector<int> parents(n, -1);
			vector<int> depths(n, 1);

			// Run kruskal excluding this edge
			int size = kruskal(n, edges, orderedEdges, i, -1);
			if (size > best) {
				ans[0].push_back(i);
			} else {
				// Run kruskal using this edge
				int size = kruskal(n, edges, orderedEdges, -1, i);
				if (size == best) {
					ans[1].push_back(i);
				}
			}
		}

		return ans;
	}

private:
	int kruskal(int n, const vector<vector<int>>& edges, const vector<pair<int, int>>& orderedEdges, int removedEdgeIndex, int initialUseEdgeIndex) {
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

		for (const auto& p : orderedEdges) {
			const int& d = p.first;
			const int& edgeIndex = p.second;
			if (edgeIndex == removedEdgeIndex) continue;

			const int& u = edges[edgeIndex][0];
			const int& v = edges[edgeIndex][1];

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