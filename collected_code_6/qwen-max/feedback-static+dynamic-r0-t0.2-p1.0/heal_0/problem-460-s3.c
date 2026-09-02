#include <stdio.h>
#include <stdlib.h>

int* get_first_elements(int** list, int size, int* output_size) {
    *output_size = 0;
    for (int i = 0; i < size; ++i) {
        if (list[i] == NULL || list[i][0] == 0) {
            continue;
        }
        (*output_size)++;
    }

    int* result = (int*)malloc(*output_size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < size; ++i) {
        if (list[i] != NULL && list[i][0] != 0) {
            result[index++] = list[i][0];
        }
    }

    return result;
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 6};
    int list3[] = {7, 8, 9};
    int list4[] = {10, 11, 12};

    int* lists[] = {list1, list2, list3, list4};
    int size = 4;

    int output_size;
    int* first_elements = get_first_elements(lists, size, &output_size);

    if (first_elements != NULL) {
        for (int i = 0; i < output_size; ++i) {
            printf("%d ", first_elements[i]);
        }
        free(first_elements);
    } else {
        printf("Failed to allocate memory\n");
    }

    return 0;
}