#include <iostream>
#include <unordered_map>
#include <assert.h>
#include <vector>
#include <algorithm>

struct Node {
    size_t next;
    size_t key;
    size_t rank;
};

struct Edge {
    size_t dest;
    double weight; 
};

struct Graph {
    size_t v, e;

    std::vector<std::vector<Edge>> arr;

    Graph(size_t v) {
        arr.resize(v);
        this-> v = v;
    };

    inline void add_edge(size_t u, size_t v, size_t w) {
        this->arr[u].push_back({v, w});
        this->arr[v].push_back({u, w});
    };

    bool is_edge(size_t u, size_t v) {
        return std::find(arr[u].begin(), arr[u].end(), v) !=  arr[u].end();
    };

};

struct UnionFind {
    Node* arr;

    UnionFind(size_t n) {
        arr = (Node*) malloc(sizeof(struct Node) * n);
    }

    void setunion(size_t x, size_t y) {
        link(find(x), find(y));
    };

    void makeset(size_t x) {
        arr[x].next = x;
        arr[x].key = x;
        arr[x].rank = 1;
    };

    size_t find(size_t x) {
        if (x != arr[x].next) {
            arr[x].next = find(arr[x].next);
            return arr[x].next;
        } else {
            return x;
        }
    };

    void link(size_t x, size_t y) {

        if (arr[x].rank > arr[y].rank) {
            arr[y].next = x;
        } else if (arr[x].rank == arr[y].rank) {
            arr[y].rank ++;
            arr[x].next = y;
        } else if (arr[x].rank < arr[y].rank) {
            arr[x].next = y;
        }

    };
};

void test_setunion() {
    assert(true);
}

int main() {
    test_setunion();

}
