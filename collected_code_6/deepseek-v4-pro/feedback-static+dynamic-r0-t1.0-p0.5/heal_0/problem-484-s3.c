#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int remove_matching_tuples(Tuple *tuple1, int *size1, Tuple *tuple2, int *size2) {
    if (tuple1 == NULL || tuple2 == NULL || size1 == NULL || size2 == NULL) {
        return -1;
    }
    if (*size1 < 0 || *size2 < 0) {
        return -1;
    }

    int i = 0;
    while (i < *size1) {
        int j = 0;
        int found = 0;
        while (j < *size2) {
            if (tuple1[i].first == tuple2[j].first && tuple1[i].second == tuple2[j].second) {
                found = 1;
                break;
            }
            j++;
        }
        if (found) {
            for (int k = i; k < *size1 - 1; k++) {
                tuple1[k] = tuple1[k + 1];
            }
            (*size1)--;
        } else {
            i++;
        }
    }

    i = 0;
    while (i < *size2) {
        int j = 0;
        int found = 0;
        while (j < *size1) {
            if (tuple2[i].first == tuple1[j].first && tuple2[i].second == tuple1[j].second) {
                found = 1;
                break;
            }
            j++;
        }
        if (found) {
            for (int k = i; k < *size2 - 1; k++) {
                tuple2[k] = tuple2[k + 1];
            }
            (*size2)--;
        } else {
            i++;
        }
    }

    return 0;
}

int main(void) {
    Tuple tuple1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    Tuple tuple2[] = {{3, 4}, {5, 6}, {9, 10}};
    int size1 = 4;
    int size2 = 3;

    if (remove_matching_tuples(tuple1, &size1, tuple2, &size2) != 0) {
        fprintf(stderr, "Error removing matching tuples\n");
        return EXIT_FAILURE;
    }

    printf("Tuple1 after removal: ");
    for (int i = 0; i < size1; i++) {
        printf("(%d, %d) ", tuple1[i].first, tuple1[i].second);
    }
    printf("\n");

    printf("Tuple2 after removal: ");
    for (int i = 0; i < size2; i++) {
        printf("(%d, %d) ", tuple2[i].first, tuple2[i].second);
    }
    printf("\n");

    return EXIT_SUCCESS;
}