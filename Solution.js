
/**
 * @param {number[]} nums
 * @param {number[]} removeQueries
 * @return {number[]}
 */
var maximumSegmentSum = function (nums, removeQueries) {

    const unionFind = new UnionFind(nums.length);
    const maxSegmentSum = new Array(nums.length).fill(0);
    let currentMax = 0;

    for (let i = nums.length - 1; i >= 0; --i) {
        let query = removeQueries[i];
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
};

class UnionFind {

    constructor(sizeInput) {
        this.parent = Array.from(new Array(sizeInput).keys());
        this.rank = new Array(sizeInput).fill(0);
    }

    findParent(index) {
        if (this.parent[index] !== index) {
            this.parent[index] = this.findParent(this.parent[index]);
        }
        return this.parent[index];
    }

    joinByRank(indexOne, indexTwo) {
        if (this.rank[indexOne] >= this.rank[indexTwo]) {
            this.rank[indexOne] += this.rank[indexTwo];
            this.parent[indexTwo] = indexOne;
        } else {
            this.rank[indexTwo] += this.rank[indexOne];
            this.parent[indexOne] = indexTwo;
        }
    }
}
