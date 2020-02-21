#include <iostream>
#include <unordered_map>

int main() {
    std::cout << "Hello World!";
}


struct heaptype {
    double weight;
    void* ptr;
};

struct heap{
    heaptype* arr; // Array is one bigger; let first element start at one
    size_t max_size;

    size_t used_size;

    std::unordered_map<void*, size_t> m;

    heap(size_t n) {
        arr = (heaptype*) malloc(sizeof(heaptype) * (n+1));
        max_size = n;
    };
    ~heap() {
        free(arr);
    };

    inline void swap_els(heaptype* a, heaptype* b) {
        heaptype temp = *a;
        *a = *b;
        *b = temp;
    }

    heaptype peek() {

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

    heaptype remove();
    heaptype remove_and_add(heaptype i);
    void add(heaptype i);
    void alter(void* ptr, double weight) {

    };
};