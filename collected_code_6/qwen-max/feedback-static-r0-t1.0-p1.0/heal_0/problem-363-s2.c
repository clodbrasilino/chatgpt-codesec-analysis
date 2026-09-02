#include <stdio.h>
#include <stdlib.h>

void add_k_to_tuple(int *tuple, int length, int k) {
    for (int i = 0; i < length; ++i) {
        tuple[i] += k;
    }
}

int main() {
    int length = 5;
    int k = 3;
    int *tuple = (int *)malloc(length * sizeof(int));

    if (tuple == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < length; ++i) {
        tuple[i] = i + 1;
    }

    add_k_to_tuple(tuple, length, k);

    for (int i = 0; i < length; ++i) {
        printf("%d ", tuple[i]);
    }
    printf("\n");

    free(tuple);
    return EXIT_SUCCESS;
}