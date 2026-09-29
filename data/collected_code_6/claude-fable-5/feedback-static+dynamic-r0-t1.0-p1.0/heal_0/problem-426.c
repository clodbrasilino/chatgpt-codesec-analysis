#include <stdio.h>
#include <stdlib.h>

int *filter_odd(const int *input, size_t count, size_t *result_count)
{
    int *result;
    size_t i;
    size_t n;

    if (input == NULL || result_count == NULL) {
        return NULL;
    }

    *result_count = 0;

    if (count == 0) {
        return NULL;
    }

    n = 0;
    for (i = 0; i < count; i++) {
        if (input[i] % 2 != 0) {
            n++;
        }
    }

    if (n == 0) {
        return NULL;
    }

    result = malloc(n * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    n = 0;
    for (i = 0; i < count; i++) {
        if (input[i] % 2 != 0) {
            result[n] = input[i];
            n++;
        }
    }

    *result_count = n;
    return result;
}

int main(void)
{
    int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t odd_count = 0;
    size_t i;
    int *odds;

    odds = filter_odd(numbers, count, &odd_count);
    if (odds == NULL) {
        if (odd_count == 0) {
            printf("No odd numbers found.\n");
            return EXIT_SUCCESS;
        }
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Odd numbers:");
    for (i = 0; i < odd_count; i++) {
        printf(" %d", odds[i]);
    }
    printf("\n");

    free(odds);
    return EXIT_SUCCESS;
}