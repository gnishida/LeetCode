#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
	int longestIncreasingPath(vector<vector<int>>& matrix) {
		int M = matrix.size();
		if (M == 0) return 0;
		int N = matrix[0].size();

		const vector<pair<pair<int, int>, int>> dirs = { {{1, 0}, N}, {{0, 1}, 1}, {{-1, 0}, -N}, {{0, -1}, -1} };
		vector<vector<int>> outEdges(M * N);
		vector<int> numInEdges(M * N, 0);
		int index = 0;
		for (int r = 0; r < M; r++) {
			for (int c = 0; c < N; c++) {
				for (const auto& dir : dirs) {
					int rr = r + dir.first.first;
					int cc = c + dir.first.second;
					if (rr < 0 || rr >= M || cc < 0 || cc >= N) continue;
					int d = dir.second;
					if (matrix[rr][cc] > matrix[r][c]) {
						outEdges[index].push_back(index + d);
						numInEdges[index + d]++;
					}
				}

				index++;
			}
		}

		queue<int> Q;
		for (int i = 0; i < numInEdges.size(); i++) {
			if (numInEdges[i] == 0) {
				Q.push(i);
			}
		}

		int ans = 1;
		vector<int> D(M * N, 1);
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();

			ans = max(ans, D[u]);

			for (const auto& v : outEdges[u]) {
				D[v] = max(D[v], D[u] + 1);

				if (--numInEdges[v] == 0) {
					Q.push(v);
				}
			}
		}

		return ans;
	}
};

int main() {
	vector<vector<int>> matrix = {
		{9,9,4},
		{6,6,8},
		{2,1,1}
	};

	Solution sol;
	cout << sol.longestIncreasingPath(matrix) << endl;


	return 0;
}