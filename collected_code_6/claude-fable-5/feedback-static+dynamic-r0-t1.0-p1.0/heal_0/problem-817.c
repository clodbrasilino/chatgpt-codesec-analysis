#include <stdio.h>
#include <stdlib.h>

int find_divisible(const int *numbers, size_t count, int m, int n,
                   int **result, size_t *result_count)
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
    if (count == 0) {
        *result = NULL;
        *result_count = 0;
        return 0;
    }

    buffer = malloc(count * sizeof(int));
    if (buffer == NULL) {
        return -1;
    }

    found = 0;
    for (i = 0; i < count; i++) {
        if ((numbers[i] % m == 0) || (numbers[i] % n == 0)) {
            buffer[found] = numbers[i];
            found++;
        }
    }

    if (found == 0) {
        free(buffer);
        *result = NULL;
        *result_count = 0;
        return 0;
    }

    *result = buffer;
    *result_count = found;
    return 0;
}

int main(void)
{
    int numbers[] = {19, 65, 57, 39, 152, 639, 121, 44, 90, 190};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int m = 19;
    int n = 13;
    int *result = NULL;
    size_t result_count = 0;
    size_t i;

    if (find_divisible(numbers, count, m, n, &result, &result_count) != 0) {
        fprintf(stderr, "Error: failed to find divisible numbers\n");
        return EXIT_FAILURE;
    }

    printf("Numbers divisible by %d or %d:\n", m, n);
    for (i = 0; i < result_count; i++) {
        printf("%d\n", result[i]);
    }

    free(result);
    return EXIT_SUCCESS;
}