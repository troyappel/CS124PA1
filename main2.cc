#include <iostream>
#include <unordered_map>

struct Node {
    size_t next;
    size_t key;
};

struct UnionFind {
    Node* arr;

    UnionFind(size_t n) {
        arr = (Node*) malloc(sizeof(struct Node) * n);
    }

    void setunion(size_t x, size_t y) {

    };

    void makeset(size_t x) {
        arr[x].next = arr[x];
    };

    size_t find(size_t x) {
        if (x != arr[x].next) {
            arr[x].next = find(arr[x].next);
            return arr[x].next;
        } else {
            return x;
        }
    };

    size_t link(size_t x, size_t y) {

    };
};

int main() {

}
