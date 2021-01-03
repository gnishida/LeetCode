#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
	int reachableNodes(vector<vector<int>>& edges, int M, int N) {
		vector<int> DP(N, numeric_limits<int>::max());
		DP[0] = 0;

		vector<vector<pair<int, int>>> adj(N);
		for (const auto& edge : edges) {
			const auto& u = edge[0];
			const auto& v = edge[1];
			const auto& w = edge[2];
			adj[u].push_back({ v, w + 1 });
			adj[v].push_back({ u, w + 1 });
		}

		int ans = 0;
		vector<bool> finished(N, false);
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
		Q.push({ 0, 0 });
		while (!Q.empty()) {
			int d = Q.top().first;
			int u = Q.top().second;
			Q.pop();
			if (d > DP[u] || DP[u] > M) continue;

			// Process vertex u
			ans++;
			finished[u] = true;

			for (const auto& p : adj[u]) {
				const auto& v = p.first;
				const auto& w = p.second;
				
				// Count the number of points that are already counted
				int used = 0;
				if (finished[v] && M > DP[v]) {
					used = min(w - 1, M - DP[v]);
				}

				ans += min(w - 1 - used, M - DP[u]);

				// Update neighbor vertex v
				int new_d = DP[u] + w;
				if (new_d < DP[v]) {
					DP[v] = new_d;
					Q.push({ new_d, v });
				}
			}
		}

		return ans;
	}
};

int main() {
	vector<vector<int>> edges = { {1,2,5},{0,3,3},{1,3,2},{2,3,4},{0,4,1} };

	Solution sol;
	cout << sol.reachableNodes(edges, 7, 5) << endl;

	return 0;
}