
#include <vector>
using namespace std;

class UnionFind {
    
public:
    vector<int> parent;
    vector<long long> rank;

    UnionFind(size_t sizeInput) {
        parent.resize(sizeInput);
        iota(parent.begin(), parent.end(), 0);
        rank.resize(sizeInput);
    }

    int findParent(int index) {
        if (parent[index] != index) {
            parent[index] = findParent(parent[index]);
        }
        return parent[index];
    }

    void joinByRank(int indexOne, int indexTwo) {
        if (rank[indexOne] >= rank[indexTwo]) {
            rank[indexOne] += rank[indexTwo];
            parent[indexTwo] = indexOne;
        } else {
            rank[indexTwo] += rank[indexOne];
            parent[indexOne] = indexTwo;
        }
    }
};

class Solution {
    
public:
    vector<long long> maximumSegmentSum(vector<int>& nums, vector<int>& removeQueries) {
        
        UnionFind unionFind(nums.size());
        vector<long long> maxSegmentSum(nums.size());
        long currentMax = 0;
        
        for (int i = nums.size() - 1; i >= 0; --i) {
            int query = removeQueries[i];
            maxSegmentSum[i] = currentMax;
            unionFind.rank[query] = nums[query];

            if (query - 1 >= 0 && unionFind.rank[query - 1] > 0) {
                unionFind.joinByRank(unionFind.findParent(query - 1), unionFind.findParent(query));
            }
            if (query + 1 < nums.size() && unionFind.rank[query + 1] > 0) {
                unionFind.joinByRank(unionFind.findParent(query + 1), unionFind.findParent(query));
            }
            currentMax = currentMax > unionFind.rank[unionFind.findParent(query)] ?
                         currentMax : unionFind.rank[unionFind.findParent(query)];
        }
        return maxSegmentSum;
    }
};
