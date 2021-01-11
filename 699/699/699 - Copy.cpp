#include <iostream>
#include <vector>
#include <algorithm>
#include <map>


using namespace std;


class SegmentTree {
public:
	SegmentTree(int n) {
		N = n;
		treeData.resize(n * 4, 0);
	}

	// Add the value to the index-th element
	void setRange(int query_left, int query_right, long long val) {
		setRange(1, 0, N - 1, query_left, query_right, val);
	}

	void setRange(int index, int left, int right, int query_left, int query_right, long long val) {
		if (left == right) {
			treeData[index] = val;
			return;
		}

		int m = (left + right) / 2;
		if (query_left <= m) {
			setRange(index * 2, left, m, query_left, min(m, query_right), val);
		}
		if (query_right > m) {
			setRange(index * 2 + 1, m + 1, right, max(m + 1, query_left), query_right, val);
		}

		treeData[index] = max(treeData[index * 2], treeData[index * 2 + 1]);
	}

	// Get max of elements between query_left and query_right
	long long query(int query_left, int query_right) {
		return query(1, 0, N - 1, query_left, query_right);
	}

	long long query(int index, int left, int right, int query_left, int query_right) {
		if (left == query_left && right == query_right) return treeData[index];

		long long ans = 0;

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
	vector<long long> treeData;
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

			segTree.setRange(left, right, max_height);

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