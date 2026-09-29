#include <stdio.h>
#include <stdlib.h>

int *find_greater_than(const int *list, size_t size, int threshold, size_t *result_count)
{
    int *result = NULL;
    size_t count = 0;
    size_t i;

    if (list == NULL || result_count == NULL) {
        return NULL;
    }

    *result_count = 0;

    for (i = 0; i < size; i++) {
        if (list[i] > threshold) {
            count++;
        }
    }

    if (count == 0) {
        return NULL;
    }

    result = malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    count = 0;
    for (i = 0; i < size; i++) {
        if (list[i] > threshold) {
            result[count] = list[i];
            count++;
        }
    }

    *result_count = count;
    return result;
}

int main(void)
{
    int values[] = {3, 15, 7, 22, 9, 1, 30, 12};
    size_t size = sizeof(values) / sizeof(values[0]);
    int threshold = 10;
    size_t result_count = 0;
    size_t i;
    int *result;

    result = find_greater_than(values, size, threshold, &result_count);

    if (result == NULL) {
        if (result_count == 0) {
            printf("No values greater than %d found.\n", threshold);
            return EXIT_SUCCESS;
        }
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Values greater than %d:\n", threshold);
    for (i = 0; i < result_count; i++) {
        printf("%d\n", result[i]);
    }

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}