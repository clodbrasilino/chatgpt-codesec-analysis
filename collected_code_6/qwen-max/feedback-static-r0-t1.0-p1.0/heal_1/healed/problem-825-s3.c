#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int* get_elements(const int *list, int size, const int *indices, int indices_count, int *output_count) {
    int *result = (int *)malloc(indices_count * sizeof(int));
    if (result == NULL) {
        *output_count = 0;
        return NULL;
    }
    for (int i = 0; i < indices_count; i++) {
        if (indices[i] >= 0 && indices[i] < size) {
            result[i] = list[indices[i]];
        }
    }
    *output_count = indices_count;
    return result;
}

int main() {
    int list[MAX_SIZE] = {1, 2, 3, 4, 5};
    int size = 5;
    int indices[] = {1, 3, 0};
    int indices_count = 3;
    int output_count;

    int *result = get_elements(list, size, indices, indices_count, &output_count);
    if (result != NULL) {
        for (int i = 0; i < output_count; i++) {
            printf("%d ", result[i]);
        }
        free(result);
    }

    return 0;
}