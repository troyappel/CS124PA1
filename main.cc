#include <iostream>
#include <unordered_map>




struct heaptype {
    double weight;
    size_t el;
};

struct heaptype* newHeaptype(double w, size_t el) 
{ 
    struct heaptype* h = (struct heaptype*)malloc(sizeof(struct heaptype)); 
    h->weight = w; 
    h->el = el; 
    return h; 
};

struct Heap{
    heaptype* arr; // Array is one bigger; let first element start at one
    size_t max_size;

    size_t used_size;

    std::unordered_map<size_t, size_t> m;

    Heap(size_t n) {
        arr = (heaptype*) malloc(sizeof(heaptype) * (n+1));
        max_size = n;
        used_size = 0;
    };
    ~Heap() {
        free(arr);
    };

    inline void swap_els(heaptype* a, heaptype* b) {
        heaptype temp = *a;
        *a = *b;
        *b = temp;
    }

    heaptype peek() {
        return arr[1];
    };

    void heapify() {
        size_t i = 1;
        while (true) {
            if(arr[i].weight > arr[2*i].weight) {
                swap_els(&arr[i], &arr[2*i]);
                i = 2*i;
                continue;
            } else if (arr[i].weight > arr[2*i+1].weight) {
                swap_els(&arr[i], &arr[2*i + 1]);
                i = 2*i + 1;
                continue;
            }

            break;

        }
    }

    void insert(heaptype a) {
        used_size ++;
        size_t i = used_size;
        arr[used_size] = a;
        while(arr[i].weight > arr[i/2].weight) {
            swap_els(&arr[i], &arr[i/2]);
        } //Coalesce upwards
    };

    heaptype pop() {
        heaptype min = arr[1];
        arr[1] = arr[used_size];
        heapify();
        return min;
    };

    heaptype remove_and_add(heaptype i);
    void add(heaptype i);


    void alter(heaptype a) {
    };

    void remove() {

    };

    bool empty() {
        return used_size == 0;
    }
};

int main() {
    Heap p(100);
    p.insert(heaptype{2, 1});
    p.insert(heaptype{1, 2});
    p.insert(heaptype{5, 3});
    p.insert(heaptype{3, 4});
    p.insert(heaptype{6, 5});

    while(!p.empty()) {
        printf("%i", p.pop().el);
    }

}
