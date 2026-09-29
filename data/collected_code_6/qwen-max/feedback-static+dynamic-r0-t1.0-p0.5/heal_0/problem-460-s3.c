#include <stdio.h>
#include <stdlib.h>

int* get_first_elements(int** list, int size, int* output_size) {
    *output_size = 0;
    if (list == NULL || size <= 0) {
        return NULL;
    }

    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; ++i) {
        if (list[i] != NULL && list[i][0] != 0) {
            result[(*output_size)++] = list[i][0];
        }
    }

    return result;
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 6};
    int list3[] = {7, 8, 9};

    int* lists[] = {list1, list2, list3};
    int size = 3;

    int output_size;
    int* first_elements = get_first_elements(lists, size, &output_size);

    if (first_elements != NULL) {
        for (int i = 0; i < output_size; ++i) {
            printf("%d ", first_elements[i]);
        }
        free(first_elements);
    } else {
        printf("Failed to get first elements.\n");
    }

    return 0;
}