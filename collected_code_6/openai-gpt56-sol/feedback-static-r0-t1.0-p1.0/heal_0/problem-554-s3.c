#include <stdio.h>
#include <stdlib.h>

static int find_odd_numbers(const int *numbers, size_t count, int **odd_numbers, size_t *odd_count)
{
    size_t count_found = 0;

    if (numbers == NULL || odd_numbers == NULL || odd_count == NULL) {
        return -1;
    }

    *odd_numbers = NULL;
    *odd_count = 0;

    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] % 2 != 0) {
            ++count_found;
        }
    }

    if (count_found == 0) {
        return 0;
    }

    if (count_found > SIZE_MAX / sizeof(**odd_numbers)) {
        return -1;
    }

    int *result = malloc(count_found * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    size_t result_index = 0;
    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] % 2 != 0) {
            result[result_index++] = numbers[i];
        }
    }

    *odd_numbers = result;
    *odd_count = count_found;
    return 0;
}

int main(void)
{
    const int mixed_list[] = {12, -7, 4, 19, 0, 8, -3, 22, 15};
    const size_t list_count = sizeof(mixed_list) / sizeof(mixed_list[0]);
    int *odd_numbers = NULL;
    size_t odd_count = 0;

    if (find_odd_numbers(mixed_list, list_count, &odd_numbers, &odd_count) != 0) {
        fputs("Failed to find odd numbers.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < odd_count; ++i) {
        if (printf("%d%s", odd_numbers[i], i + 1 < odd_count ? " " : "\n") < 0) {
            free(odd_numbers);
            return EXIT_FAILURE;
        }
    }

    if (odd_count == 0 && puts("No odd numbers found.") == EOF) {
        free(odd_numbers);
        return EXIT_FAILURE;
    }

    free(odd_numbers);
    return EXIT_SUCCESS;
}