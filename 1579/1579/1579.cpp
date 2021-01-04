#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
		sort(edges.begin(), edges.end(), [](const auto& e1, const auto& e2) {
			return e1[0] > e2[0];
		});

		vector<vector<int>> parents(2, vector<int>(n, -1));

		int ans = edges.size();
		vector<int> numGroups(2, n);
		for (const auto& edge : edges) {
			const auto type = edge[0];
			const auto u = edge[1] - 1;
			const auto v = edge[2] - 1;

			// Merge
			if (type == 1) {
				if (merge(parents[0], u, v, numGroups[0])) ans--;
			} else if (type == 2) {
				if (merge(parents[1], u, v, numGroups[1])) ans--;
			} else {
				bool ret1 = merge(parents[0], u, v, numGroups[0]);
				bool ret2 = merge(parents[1], u, v, numGroups[1]);
				if (ret1 || ret2) ans--;
			}
		}

		if (numGroups[0] == 1 && numGroups[1] == 1) return ans;
		else return -1;
	}

private:
	int getRoot(vector<int>& parents, int u) {
		if (parents[u] == -1) return u;

		int root = getRoot(parents, parents[u]);
		parents[u] = root;

		return root;
	}

	bool merge(vector<int>& parents, int u, int v, int& numGroups) {
		int root_u = getRoot(parents, u);
		int root_v = getRoot(parents, v);

		if (root_u != root_v) {
			parents[root_v] = root_u;
			numGroups--;
			return true;
		} else {
			return false;
		}
	}
};


int main() {
	vector<vector<int>> edges = { {3,1,2},{3,2,3},{1,1,3},{1,2,4},{1,1,2},{2,3,4}};

	Solution sol;
	cout << sol.maxNumEdgesToRemove(4, edges) << endl;

	return 0;
}