#include <iostream>

int main() {
    std::cout << "Hello World!";
}

template<typename I, typename J>
struct heap{
    int array[];

    heap(size_t n) {
        array = malloc(n);
    };
    ~heap() {
        free(array);
    };

    J peek();
    J remove();
    J remove_and_add(I i);
};