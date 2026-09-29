#include <stdbool.h>

bool containsK(const int tuples[], int k, int size) {
    for (int i = 0; i < size; i++) {
        if (tuples[i] == k) {
            return true;
        }
    }
    return false;
}

int main() {
    int array[5] = {1, 2, 3, 4, 5};
    int K = 3;
    int SIZE = sizeof(array) / sizeof(array[0]);
    
    bool found = containsK(array, K, SIZE);
    
    return 0;
}