#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
		vector<vector<pair<int, int>>> adj(n);
		for (const auto& flight : flights) {
			const auto& u = flight[0];
			const auto& v = flight[1];
			const auto& w = flight[2];
			adj[u].push_back({ v, w });
		}

		// Dijkstra
		vector<vector<int>> D(n, vector<int>(K + 2, numeric_limits<int>::max()));
		D[src][0] = 0;
		priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> Q;
		Q.push({ 0, {src, 0} });
		while (!Q.empty()) {
			const auto d = Q.top().first;
			const auto u = Q.top().second.first;
			const auto k = Q.top().second.second;
			Q.pop();

			if (d > D[u][k]) continue;
			if (k > K) continue;

			for (const auto& p : adj[u]) {
				const auto& v = p.first;
				const auto& w = p.second;

				int new_dist = d + w;
				if (new_dist < D[v][k + 1]) {
					D[v][k + 1] = new_dist;
					Q.push({ new_dist, {v, k + 1} });
				}
			}
		}

		// Find the best
		int ans = numeric_limits<int>::max();
		for (int k = 0; k <= K + 1; k++) {
			ans = min(ans, D[dst][k]);
		}

		if (ans < numeric_limits<int>::max()) {
			return ans;
		} else {
			return -1;
		}
	}
};

int main() {
	vector<vector<int>> flights = {
		{0, 1, 100},
		{1, 2, 100},
		{0, 2, 500}
	};

	Solution sol;
	cout << sol.findCheapestPrice(3, flights, 0, 2, 0) << endl;

	return 0;
}
