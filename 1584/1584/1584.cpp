#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
	int minCostConnectPoints(vector<vector<int>>& points) {
		int N = points.size();
		vector<vector<int>> adj(N, vector<int>(N));
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				int d = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
				adj[i][j] = d;
				adj[j][i] = d;
			}
		}

		// Run Prim algorithm
		int ans = 0;
		vector<int> D(N, numeric_limits<int>::max());
		D[0] = 0;
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
		Q.push({ 0, 0 });
		while (!Q.empty()) {
			int d = Q.top().first;
			int u = Q.top().second;
			Q.pop();

			if (d > D[u]) continue;

			// Add vertex u to MST
			ans += D[u];
			D[u] = 0;
			
			// Update distances for the neighbors
			for (int v = 0; v < N; v++) {
				if (D[v] == 0) continue;

				const auto& d = adj[u][v];
				if (d < D[v]) {
					D[v] = d;
					Q.push({ d, v });
				}
			}
		}

		return ans;
	}
};


int main() {
	vector<vector<int>> points = {{0,0},{2,2},{3,10},{5,2},{7,0}};

	Solution sol;
	cout << sol.minCostConnectPoints(points) << endl;



	return 0;
}