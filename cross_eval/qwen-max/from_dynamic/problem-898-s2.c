#include <stdio.h>
#include <stdlib.h>

int* extract_elements(int* list, int list_size, int start_index, int count, int* result_size) {
    if (start_index < 0 || start_index + count > list_size || count <= 0) {
        *result_size = 0;
        return NULL;
    }

    int* result = (int*) malloc(count * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < count; ++i) {
        result[i] = list[start_index + i];
    }

    *result_size = count;
    return result;
}

void free_result(int* result) {
    free(result);
}

int main() {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int list_size = sizeof(list) / sizeof(list[0]);
    int start_index = 2;
    int count = 4;

    int result_size;
    int* result = extract_elements(list, list_size, start_index, count, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; ++i) {
            printf("%d ", result[i]);
        }
        free_result(result);
    } else {
        printf("Failed to extract elements.\n");
    }

    return 0;
}