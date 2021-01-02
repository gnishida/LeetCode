#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
	int reversePairs(vector<int>& nums) {
		// Find unique numbers
		set<long long> uniqueNums;
		for (const auto& num : nums) {
			uniqueNums.insert(num);
			uniqueNums.insert((long long)num * 2);
		}

		// Assign indices to the unique numbers
		unordered_map<long long, int> indices;
		int i = 0;
		for (const auto& num : uniqueNums) {
			indices[num] = i++;
		}

		// Initialize segment tree
		int N = indices.size();
		vector<int> segTree(N * 4);

		// Use segment tree to count the important revers pairs
		int ans = 0;
		for (const auto& num : nums) {
			ans += query(segTree, 1, 0, N - 1, indices[(long long)num * 2] + 1, N - 1);
			update(segTree, 1, 0, N - 1, indices[num], 1);
		}

		return ans;
	}

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
	Solution sol;
	//vector<int> nums = { 1, 3, 2, 3, 1 };
	vector<int> nums = { 2147483647,2147483647,2147483647,2147483647,2147483647,2147483647 };
	cout << sol.reversePairs(nums) << endl;


	return 0;
}