#include <stdio.h>
#include <stdlib.h>

int* get_first_elements(int** list, int size, int* sublist_sizes) {
    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        if (sublist_sizes[i] > 0) {
            result[i] = list[i][0];
        } else {
            result[i] = 0; // Assuming 0 as a default value for empty sublists
        }
    }
    return result;
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 6};
    int list3[] = {7, 8, 9};
    int list4[] = {};

    int* lists[] = {list1, list2, list3, list4};
    int sublist_sizes[] = {3, 3, 3, 0};
    int size = 4;

    int* first_elements = get_first_elements(lists, size, sublist_sizes);
    if (first_elements != NULL) {
        for (int i = 0; i < size; ++i) {
            printf("%d ", first_elements[i]);
        }
        free(first_elements);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}