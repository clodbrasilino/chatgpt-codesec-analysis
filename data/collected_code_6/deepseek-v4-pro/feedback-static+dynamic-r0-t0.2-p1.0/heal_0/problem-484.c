#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int tuple_equals(Tuple a, Tuple b) {
    return a.first == b.first && a.second == b.second;
}

int remove_matching_tuples(Tuple *arr1, int *size1, Tuple *arr2, int *size2) {
    if (arr1 == NULL || arr2 == NULL || size1 == NULL || size2 == NULL) {
        return -1;
    }
    if (*size1 < 0 || *size2 < 0) {
        return -1;
    }

    int write1 = 0;
    int write2 = 0;

    for (int i = 0; i < *size1; i++) {
        int matched = 0;
        for (int j = 0; j < *size2; j++) {
            if (tuple_equals(arr1[i], arr2[j])) {
                matched = 1;
                break;
            }
        }
        if (!matched) {
            arr1[write1++] = arr1[i];
        }
    }

    for (int i = 0; i < *size2; i++) {
        int matched = 0;
        for (int j = 0; j < *size1; j++) {
            if (tuple_equals(arr2[i], arr1[j])) {
                matched = 1;
                break;
            }
        }
        if (!matched) {
            arr2[write2++] = arr2[i];
        }
    }

    *size1 = write1;
    *size2 = write2;

    return 0;
}

int main(void) {
    Tuple arr1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    Tuple arr2[] = {{3, 4}, {9, 10}, {1, 2}};
    int size1 = 4;
    int size2 = 3;

    if (remove_matching_tuples(arr1, &size1, arr2, &size2) != 0) {
        fprintf(stderr, "Error processing tuples\n");
        return EXIT_FAILURE;
    }

    printf("Array 1 after removal: ");
    for (int i = 0; i < size1; i++) {
        printf("(%d, %d) ", arr1[i].first, arr1[i].second);
    }
    printf("\n");

    printf("Array 2 after removal: ");
    for (int i = 0; i < size2; i++) {
        printf("(%d, %d) ", arr2[i].first, arr2[i].second);
    }
    printf("\n");

    return EXIT_SUCCESS;
}