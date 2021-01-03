#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
	int countRangeSum(vector<int>& nums, int lower, int upper) {
		if (nums.size() == 0) return 0;

		// Calculate prefix sum
		vector<long long> prefixSum(nums.size() + 1, 0);
		set<long long> distinctNums;
		distinctNums.insert(0);
		for (int i = 0; i < nums.size(); i++) {
			prefixSum[i + 1] = prefixSum[i] + nums[i];
			distinctNums.insert(prefixSum[i + 1]);
			distinctNums.insert(prefixSum[i + 1] - lower);
			distinctNums.insert(prefixSum[i + 1] - upper);
		}

		// Assign index for each prefix sum number
		int N = distinctNums.size();
		int index = 0;
		unordered_map<long long, int> indices;
		for (const auto& num : distinctNums) {
			indices[num] = index++;
		}

		// Segment tree
		int ans = 0;
		vector<int> segTree(N * 4);
		update(segTree, 1, 0, N - 1, indices[prefixSum[0]], 1);
		for (int i = 1; i < prefixSum.size(); i++) {
			int lower_index = indices[prefixSum[i] - upper];
			int upper_index = indices[prefixSum[i] - lower];
			ans += query(segTree, 1, 0, N - 1, lower_index, upper_index);

			update(segTree, 1, 0, N - 1, indices[prefixSum[i]], 1);
		}

		return ans;
	}

private:
	void update(vector<int>& segTree, int index, int left, int right, int query_index, int val) {
		segTree[index] += val;
		if (left == right) return;

		int m = (left + right) / 2;
		if (query_index <= m) {
			update(segTree, index * 2, left, m, query_index, val);
		} else {
			update(segTree, index * 2 + 1, m + 1, right, query_index, val);
		}
	}

	int query(vector<int>& segTree, int index, int left, int right, int query_left, int query_right) {
		if (left == query_left && right == query_right) return segTree[index];

		int ans = 0;
		int m = (left + right) / 2;
		if (query_left <= m) {
			ans += query(segTree, index * 2, left, m, query_left, min(m, query_right));
		}
		if (query_right > m) {
			ans += query(segTree, index * 2 + 1, m + 1, right, max(m + 1, query_left), query_right);
		}

		return ans;
	}
};

int main() {
	vector<int> nums = { -2,0,1,-1 };


	Solution sol;
	cout << sol.countRangeSum(nums, 1, 4) << endl;

	return 0;
}