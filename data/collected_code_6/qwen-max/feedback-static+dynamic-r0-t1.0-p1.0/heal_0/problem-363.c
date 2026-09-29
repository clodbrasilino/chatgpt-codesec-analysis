#include <stdio.h>
#include <stdlib.h>

void add_k_to_tuple(int *tuple, int len, int k) {
    for (int i = 0; i < len; ++i) {
        tuple[i] += k;
    }
}

int main() {
    int len = 5;
    int k = 3;
    int *tuple = malloc(len * sizeof(int));

    if (tuple == NULL) {
        return 1;
    }

    for (int i = 0; i < len; ++i) {
        tuple[i] = i + 1;
    }

    add_k_to_tuple(tuple, len, k);

    for (int i = 0; i < len; ++i) {
        printf("%d ", tuple[i]);
    }
    printf("\n");

    free(tuple);
    return 0;
}