#include <iostream>
#include <vector>
#include <algorithm>
#include <map>


using namespace std;


class SegmentTree {
public:
	SegmentTree(int n) {
		N = n;
		data.resize(n * 4, 0);
	}

	// Add the value to the index-th element
	void add(int query_index, int val) {
		add(1, 0, N - 1, query_index, query_index, val);
	}

	void add(int query_left, int query_right, int val) {
		add(1, 0, N - 1, query_left, query_right, val);
	}

	void add(int index, int left, int right, int query_left, int query_right, int val) {
		if (left == right) {
			data[index] = val;
			return;
		}

		int m = (left + right) / 2;
		if (query_left <= m) {
			add(index * 2, left, m, query_left, min(m, query_right), val);
		}
		if (query_right > m) {
			add(index * 2 + 1, m + 1, right, max(m + 1, query_left), query_right, val);
		}

		data[index] = max(data[index * 2], data[index * 2 + 1]);
	}

	// Get sum of elements between query_left and query_right
	int query(int query_left, int query_right) {
		return query(1, 0, N - 1, query_left, query_right);
	}

	int query(int index, int left, int right, int query_left, int query_right) {
		if (left == query_left && right == query_right) return data[index];

		int ans = 0;

		int m = (left + right) / 2;
		if (query_left <= m) {
			ans = max(ans, query(index * 2, left, m, query_left, min(m, query_right)));
		}
		if (query_right > m) {
			ans = max(ans, query(index * 2 + 1, m + 1, right, max(m + 1, query_left), query_right));
		}

		return ans;
	}

private:
	int N;
	vector<int> data;
};

class Solution {
public:
	vector<int> fallingSquares(vector<vector<int>>& positions) {
		int N = positions.size();
		map<int, int> numToIndex;
		for (int i = 0; i < N; i++) {
			const auto left = positions[i][0];
			const auto right = left + positions[i][1];
			const auto height = positions[i][1];

			numToIndex[left] = 0;
			numToIndex[right - 1] = 0;
		}

		// assign indices
		int index = 0;
		for (auto it = numToIndex.begin(); it != numToIndex.end(); it++, index++) {
			it->second = index;
		}

		SegmentTree segTree(numToIndex.size());

		vector<int> ans(N);
		for (int i = 0; i < N; i++) {
			const auto left = numToIndex[positions[i][0]];
			const auto right = numToIndex[positions[i][0] + positions[i][1] - 1];
			const auto height = positions[i][1];

			int max_height = segTree.query(left, right) + height;

			segTree.add(left, right, max_height);

			if (i == 0) {
				ans[i] = max_height;
			} else {
				ans[i] = max(ans[i - 1], max_height);
			}
		}

		return ans;
	}
};

int main() {
	vector<vector<int>> positions = {
		{1,2},{1,3}
	};

	Solution sol;
	auto ans = sol.fallingSquares(positions);
	for (const auto& a : ans) {
		cout << a << endl;
	}

	return 0;
}