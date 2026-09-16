#include <stdio.h>
#include <stdlib.h>

int *find_greater_than(const int *list, size_t size, int threshold, size_t *result_count) {
    if (list == NULL || result_count == NULL) {
        return NULL;
    }

    int *result = NULL;
    *result_count = 0;

    for (size_t i = 0; i < size; i++) {
        if (list[i] > threshold) {
            (*result_count)++;
        }
    }

    if (*result_count == 0) {
        return NULL;
    }

    result = (int *)malloc(*result_count * sizeof(int));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] > threshold) {
            result[index++] = list[i];
        }
    }

    return result;
}

int main(void) {
    int numbers[] = {5, 12, 3, 8, 21, 7, 15};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int threshold = 8;
    size_t count = 0;

    int *greater_values = find_greater_than(numbers, size, threshold, &count);

    if (greater_values != NULL) {
        printf("Values greater than %d: ", threshold);
        for (size_t i = 0; i < count; i++) {
            printf("%d", greater_values[i]);
            if (i < count - 1) {
                printf(", ");
            }
        }
        printf("\n");
        free(greater_values);
    } else {
        printf("No values greater than %d found.\n", threshold);
    }

    return 0;
}