#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int max_of_similar_indices(Tuple *list1, size_t size1, Tuple *list2, size_t size2, int *result) {
    size_t i;
    size_t min_size;
    int found = 0;

    if (list1 == NULL || list2 == NULL || result == NULL) {
        return -1;
    }

    min_size = (size1 < size2) ? size1 : size2;

    if (min_size == 0) {
        return -1;
    }

    int max_val = 0;

    for (i = 0; i < min_size; i++) {
        int current_max = list1[i].first;
        if (list1[i].second > current_max) {
            current_max = list1[i].second;
        }
        if (list2[i].first > current_max) {
            current_max = list2[i].first;
        }
        if (list2[i].second > current_max) {
            current_max = list2[i].second;
        }

        if (!found || current_max > max_val) {
            max_val = current_max;
            found = 1;
        }
    }

    *result = max_val;
    return 0;
}

int main(void) {
    Tuple list1[] = {{1, 5}, {3, 2}, {8, 4}};
    Tuple list2[] = {{2, 3}, {7, 1}, {4, 6}};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    int result = 0;

    if (max_of_similar_indices(list1, size1, list2, size2, &result) == 0) {
        printf("Maximum value at similar indices: %d\n", result);
    } else {
        fprintf(stderr, "Error: Invalid input or empty lists\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}