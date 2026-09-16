#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

static bool tuple_equal(Tuple a, Tuple b) {
    return a.first == b.first && a.second == b.second;
}

void remove_matching_tuples(Tuple *tuples1, int *size1, Tuple *tuples2, int *size2) {
    if (tuples1 == NULL || size1 == NULL || tuples2 == NULL || size2 == NULL) {
        return;
    }
    if (*size1 <= 0 || *size2 <= 0) {
        return;
    }

    bool *remove1 = calloc((size_t)*size1, sizeof(bool));
    bool *remove2 = calloc((size_t)*size2, sizeof(bool));

    if (remove1 == NULL || remove2 == NULL) {
        free(remove1);
        free(remove2);
        return;
    }

    for (int i = 0; i < *size1; ++i) {
        for (int j = 0; j < *size2; ++j) {
            if (!remove2[j] && tuple_equal(tuples1[i], tuples2[j])) {
                remove1[i] = true;
                remove2[j] = true;
                break;
            }
        }
    }

    int new_size1 = 0;
    for (int i = 0; i < *size1; ++i) {
        if (!remove1[i]) {
            tuples1[new_size1++] = tuples1[i];
        }
    }

    int new_size2 = 0;
    for (int j = 0; j < *size2; ++j) {
        if (!remove2[j]) {
            tuples2[new_size2++] = tuples2[j];
        }
    }

    *size1 = new_size1;
    *size2 = new_size2;

    free(remove1);
    free(remove2);
}

int main(void) {
    Tuple tuples1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    Tuple tuples2[] = {{3, 4}, {7, 8}, {9, 10}};
    int size1 = 4;
    int size2 = 3;

    remove_matching_tuples(tuples1, &size1, tuples2, &size2);

    for (int i = 0; i < size1; ++i) {
        printf("(%d, %d) ", tuples1[i].first, tuples1[i].second);
    }
    printf("\n");

    for (int i = 0; i < size2; ++i) {
        printf("(%d, %d) ", tuples2[i].first, tuples2[i].second);
    }
    printf("\n");

    return 0;
}