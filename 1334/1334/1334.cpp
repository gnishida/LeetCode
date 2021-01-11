#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


class Solution {
public:
	int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
		vector<vector<pair<int, int>>> E(n);
		for (const auto& edge : edges) {
			const auto& u = edge[0];
			const auto& v = edge[1];
			const auto& w = edge[2];
			E[u].push_back({ v, w });
			E[v].push_back({ u, w });
		}

		int ans = -1;
		int minNum = n - 1;
		vector<vector<int>> distances = floyd_warshall(n, E);
		for (int u = 0; u < n; u++) {
			int num = 0;
			for (int v = 0; v < n; v++) {
				if (v == u) continue;
				if (distances[u][v] <= distanceThreshold) num++;
			}

			if (num <= minNum) {
				minNum = num;
				ans = u;
			}
		}

		return ans;
	}

private:
	vector<vector<int>> floyd_warshall(int N, vector<vector<pair<int, int>>>& edges) {
		vector<vector<int>> DP(N, vector<int>(N, -1));

		// Initialize the distance between nodes
		for (int u = 0; u < N; u++) {
			for (const auto& p : edges[u]) {
				const auto& v = p.first;
				const auto& w = p.second;
				DP[u][v] = w;
			}
		}
		for (int u = 0; u < N; u++) {
			DP[u][u] = 0;
		}

		for (int k = 0; k < N; k++) {
			for (int u = 0; u < N; u++) {
				for (int v = 0; v < N; v++) {
					if (DP[u][k] >= 0 && DP[k][v] >= 0) {
						if (DP[u][v] == -1) DP[u][v] = DP[u][k] + DP[k][v];
						else DP[u][v] = min(DP[u][v], DP[u][k] + DP[k][v]);
					}
				}
			}
		}

		return DP;
	}
};

int main() {
	vector<vector<int>> edges = {
		{0,1,2},{0,4,8},{1,2,3},{1,4,2},{2,3,1},{3,4,1}
	};

	Solution sol;
	cout << sol.findTheCity(5, edges, 2) << endl;

	return 0;

}