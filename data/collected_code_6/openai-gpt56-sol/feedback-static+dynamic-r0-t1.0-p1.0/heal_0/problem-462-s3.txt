#include <stdio.h>
#include <stdlib.h>

static int print_combinations_recursive(const int *values, size_t count,
                                        int *combination, size_t index)
{
    if (index == count) {
        putchar('{');

        for (size_t i = 0; i < count; ++i) {
            if (combination[i]) {
                if (printf("%s%d", i == 0 ? "" : " ", values[i]) < 0) {
                    return -1;
                }
            }
        }

        return puts("}") == EOF ? -1 : 0;
    }

    combination[index] = 0;
    if (print_combinations_recursive(values, count, combination, index + 1) != 0) {
        return -1;
    }

    combination[index] = 1;
    return print_combinations_recursive(values, count, combination, index + 1);
}

static int print_all_combinations(const int *values, size_t count)
{
    int *combination;

    if (values == NULL && count != 0) {
        return -1;
    }

    if (count == 0) {
        return puts("{}") == EOF ? -1 : 0;
    }

    if (count > SIZE_MAX / sizeof(*combination)) {
        return -1;
    }

    combination = calloc(count, sizeof(*combination));
    if (combination == NULL) {
        return -1;
    }

    int result = print_combinations_recursive(values, count, combination, 0);
    free(combination);
    return result;
}

int main(void)
{
    const int values[] = {1, 2, 3, 4};
    const size_t count = sizeof(values) / sizeof(values[0]);

    if (print_all_combinations(values, count) != 0) {
        fputs("Failed to generate combinations.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}