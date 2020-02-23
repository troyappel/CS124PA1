#include <iostream>
#include <unordered_map>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <math.h>
#include <chrono>
#include <mutex>
#include <thread>

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


struct Graph {
    int V, E;
    std::vector<Edge> edges; 
    
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

int comp_edge(Edge a, Edge b) {
    return a.weight < b.weight;
}

class GraphGen {
    public:
        static Graph genGraph(size_t n);
        static double k_max(size_t n);
};


// NOTE: WHICH GEN TO USE? mt19937_64 is good and high-precision but minstd_rand is twice as fast
class step0Gen : public GraphGen {
    public:
        static Graph genGraph(size_t n, size_t seed) {
            std::mt19937_64 gen(seed);
            std::uniform_real_distribution<double> dist(0, 1);

            double k = k_max(n);

            Graph g;

            for (int i = 0; i < n; i++) {
                for (int j = i+1; j < n; j++) {
                    double d =  dist(gen);
                    if (d < k) {
                        g.add_edge(i, j, dist(gen));
                    }
                }
            }

            return g;

        }
        static double k_max(size_t n) {
            double ex = - 0.7 * log2((double)n);
            return pow(2.0, ex);
        };
};

std::vector<std::pair<double, double>> res;
std::mutex mtx;

void thread_func(size_t n_points, size_t t_num) {
    Graph g = step0Gen::genGraph(n_points, t_num);
    UnionFind u(n_points);
    
    sort(g.edges.begin(), g.edges.end(), comp_edge);

    double sum = 0;
    double max_weight = 0;

    size_t found = 0;

    //Kruskal's Algorithm
    for(int i = 0; i < g.edges.size() && found != n_points-1; i++) {
        int x = u.find(g.edges[i].src);
        int y = u.find(g.edges[i].dest);

        if (x != y) {
            sum += g.edges[i].weight;
            max_weight = g.edges[i].weight;
            u.setunion(x,y);
            found++;
        }

        if (i == g.edges.size() -1) {
            printf("error: not enough terms\n");
        }

    }

    printf("Sum: %.17g, Max: %.17g\n", sum, g.edges[0].weight);

    {
        std::lock_guard<std::mutex> guard(mtx); 
        res.push_back(std::make_pair(sum, g.edges[0].weight));
    }
}


int main(int argc, char **argv) {

    auto start = std::chrono::high_resolution_clock::now();

    assert(argc == 5);

    size_t f = atol(argv[1]);

    size_t n_points = atol(argv[2]);

    size_t n_trials = atol(argv[3]);

    size_t dim = atol(argv[4]);

    std::vector<std::thread> t_v;

    for(int i = 0; i < n_trials; i++) {
        t_v.push_back(std::thread(thread_func, n_points, i));
    }

    for(int i = 0; i < n_trials; i++) {
        t_v[i].join();
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop-start);

    double sum = 0.;
    double max = 0.;
    for (int i = 0; i < n_trials; i++) {
        sum += res[i].first;
        if (res[i].second > max) {
            max = res[i].second;
        }
    }

    sum /= n_trials;

    printf("Average weight: %.17g\n", sum);

    printf("Max: %.17g\n", max);

    printf("Time elapsed: %i\n", duration.count());
    
}