#include <stdio.h>

void multiplyAdjacent(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        int product = arr[i] * arr[i - 1];
        printf("%d ", product);
    }
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);

    multiplyAdjacent(tuple, size);

    return 0;
}