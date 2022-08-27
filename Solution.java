
import java.util.stream.IntStream;

public class Solution {

    public long[] maximumSegmentSum(int[] nums, int[] removeQueries) {

        UnionFind unionFind = new UnionFind(nums.length);
        long[] maxSegmentSum = new long[nums.length];
        long currentMax = 0;

        for (int i = nums.length - 1; i >= 0; --i) {
            int query = removeQueries[i];
            maxSegmentSum[i] = currentMax;
            unionFind.rank[query] = nums[query];

            if (query - 1 >= 0 && unionFind.rank[query - 1] > 0) {
                unionFind.joinByRank(unionFind.findParent(query - 1), unionFind.findParent(query));
            }
            if (query + 1 < nums.length && unionFind.rank[query + 1] > 0) {
                unionFind.joinByRank(unionFind.findParent(query + 1), unionFind.findParent(query));
            }
            currentMax = Math.max(currentMax, unionFind.rank[unionFind.findParent(query)]);
        }
        return maxSegmentSum;
    }
}

class UnionFind {

    int[] parent;
    long[] rank;

    UnionFind(int sizeInput) {
        parent = IntStream.range(0, sizeInput).toArray();
        rank = new long[sizeInput];
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
}
