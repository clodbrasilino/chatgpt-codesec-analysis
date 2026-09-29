#include <stdio.h>
#include <stdlib.h>

int* find_greater(const int* list, size_t size, int threshold, size_t* result_size) {
    if (list == NULL || result_size == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (list[i] > threshold) {
            ++count;
        }
    }

    if (count == 0) {
        *result_size = 0;
        return NULL;
    }

    int* result = (int*)malloc(count * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < size; ++i) {
        if (list[i] > threshold) {
            result[index++] = list[i];
        }
    }

    *result_size = count;
    return result;
}

int main(void) {
    int list[] = {1, 5, 8, 12, 3, 7, 10};
    size_t size = sizeof(list) / sizeof(list[0]);
    int threshold = 6;
    size_t result_size = 0;

    int* result = find_greater(list, size, threshold, &result_size);

    if (result != NULL) {
        for (size_t i = 0; i < result_size; ++i) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("No values found greater than %d\n", threshold);
    }

    return 0;
}