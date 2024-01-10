#include <stdio.h>

void add_k_to_tuple(int* tuple, const int k, const int size) {
    for (int i = 0; i < size; i++) {
        tuple[i] += k;
    }
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    const int k = 10;
    const int size = sizeof(tuple) / sizeof(tuple[0]);

    add_k_to_tuple(tuple, k, size);

    for(int i=0; i<size; i++) {
        printf("%d ", tuple[i]);
    }

    return 0;
}