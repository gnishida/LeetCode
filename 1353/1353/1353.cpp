#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

class Solution {
public:
	int maxEvents(vector<vector<int>>& events) {
		int N = events.size();

		map<int, vector<int>> E;
		for (int i = 0; i < N; i++) {
			E[events[i][0]].push_back(i);
		}

		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
		vector<bool> used(N, false);

		int ans = 0;
		int day = 1;
		for (auto it = E.begin(); it != E.end(); it++) {
			day = it->first;
			auto it2 = it;
			it2++;
			int next_day = numeric_limits<int>::max();
			if (it2 != E.end()) {
				next_day = it2->first;
			}

			for (const auto& index : it->second) {
				Q.push({ events[index][1], index });
			}

			while (!Q.empty() && day < next_day) {
				int u = Q.top().second;
				Q.pop();
				if (events[u][1] >= day) {
					day = max(day, events[u][0]);
					day++;
					ans++;
					used[u] = true;
				}
			}
		}

		return ans;
	}
};


int main() {
	vector<vector<int>> events = {
		{1,4},{4,4},{2,2},{3,4},{1,1}
	};

	Solution sol;
	cout << sol.maxEvents(events) << endl;

	return 0;
}