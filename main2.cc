#include <iostream>
#include <unordered_map>
#include <assert.h>

struct Node {
    size_t next;
    size_t key;
    size_t rank;
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
