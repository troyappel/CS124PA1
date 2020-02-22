#include <iostream>
#include <unordered_map>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>

struct Node {
    size_t next;
    size_t key;
    size_t rank;
};

struct Edge {
    size_t src;
    size_t dest;
    double weight; 
};

// struct Graph {
//     size_t v, e;

//     std::vector<std::vector<Edge>> arr;

//     Graph(size_t v) {
//         arr.resize(v);
//         this-> v = v;
//     };

//     inline void add_edge(size_t u, size_t v, size_t w) {
//         this->arr[u].push_back({v, w});
//         this->arr[v].push_back({u, w});
//     };

//     bool is_edge(size_t u, size_t v) {
//         return std::find(arr[u].begin(), arr[u].end(), v) !=  arr[u].end();
//     };

// };

struct Graph {
    int V, E;
    std::vector<Edge> edges; 

    Graph() {

    }
    
    inline void add_edge(size_t u, size_t v, double w) {
        edges.push_back({u,v,w});
    }
};

struct UnionFind {
    Node* arr;

    UnionFind(size_t n) {
        arr = (Node*) malloc(sizeof(struct Node) * n);
        for (int v = 0; v < n; v++) {
            makeset(v);
        }
    }

    void setunion(size_t x, size_t y) {
        link(find(x), find(y));
    };

    inline void makeset(size_t x) {
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

int comp_edge(const void* a, const void* b) {
    return ((Edge*) a)->weight > ((Edge*) b)->weight;
}


int main(int argc, char **argv) {
    test_setunion();

    size_t n = atol(argv[1]);

    double k = 1;
    size_t needed = n*4;

    std::minstd_rand gen(std::random_device{}());
    std::uniform_real_distribution<double> dist(0, 1);

    Graph g;
    UnionFind u(n);

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            g.add_edge(i, j, dist(gen));
        }
    }

    std::vector<Edge> results;

    sort(g.edges.begin(), g.edges.end(), comp_edge);

    for(int i = 0; i < g.edges.size(); i++) {
        int x = u.find(g.edges[i].src);
        int y = u.find(g.edges[i].dest);

        if (x != y) {
            results.push_back(g.edges[i]);
            u.setunion(x,y);
        }

    }

    for (int i = 0; i < results.size(); i++) {
        Edge e = g.edges[i];
        printf("(%i,%i), %d\n", e.src, e.dest, e.weight);
    }
    
}
