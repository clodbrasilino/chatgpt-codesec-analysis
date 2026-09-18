#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int is_k_in_tuples(Tuple* tuples, int tuple_count, int k) {
    if (tuples == NULL || tuple_count <= 0) {
        return -1;
    }

    for (int i = 0; i < tuple_count; i++) {
        if (tuples[i].a == k || tuples[i].b == k) {
            return 1;
        }
    }

    return 0;
}

int main() {
    Tuple tuples[] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    int tuple_count = sizeof(tuples) / sizeof(Tuple);

    int k = 4;
    int result = is_k_in_tuples(tuples, tuple_count, k);
    if (result == -1) {
        printf("Invalid input.\n");
        exit(EXIT_FAILURE);
    } else if (result == 1) {
        printf("The number %d is found in the tuples.\n", k);
    } else {
        printf("The number %d is not found in the tuples.\n", k);
    }

    return 0;
}