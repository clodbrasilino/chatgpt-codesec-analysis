#include <stdio.h>
#include <stdlib.h>

int find_divisible(const int *numbers, size_t count, int m, int n, int **result, size_t *result_count)
{
    size_t i;
    size_t found;
    int *buffer;

    if (numbers == NULL || result == NULL || result_count == NULL) {
        return -1;
    }

    if (m == 0 || n == 0) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (count == 0) {
        return 0;
    }

    buffer = malloc(count * sizeof(int));
    if (buffer == NULL) {
        return -1;
    }

    found = 0;
    for (i = 0; i < count; i++) {
        if ((numbers[i] % m == 0) && (numbers[i] % n == 0)) {
            buffer[found] = numbers[i];
            found++;
        }
    }

    if (found == 0) {
        free(buffer);
        buffer = NULL;
    } else if (found < count) {
        int *shrunk = realloc(buffer, found * sizeof(int));
        if (shrunk != NULL) {
            buffer = shrunk;
        }
    }

    *result = buffer;
    *result_count = found;
    return 0;
}

int main(void)
{
    int numbers[] = { 12, 15, 30, 45, 60, 7, 90, 22, 120 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int m = 3;
    int n = 5;
    int *result = NULL;
    size_t result_count = 0;
    size_t i;

    if (find_divisible(numbers, count, m, n, &result, &result_count) != 0) {
        fprintf(stderr, "Error finding divisible numbers\n");
        return EXIT_FAILURE;
    }

    printf("Numbers divisible by %d and %d:\n", m, n);
    for (i = 0; i < result_count; i++) {
        printf("%d\n", result[i]);
    }

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}