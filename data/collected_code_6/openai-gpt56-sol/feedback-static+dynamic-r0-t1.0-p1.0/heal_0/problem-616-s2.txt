#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

static bool tuple_modulo(const int *left, const int *right, int *result,
                         size_t length)
{
    if (left == NULL || right == NULL || result == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        if (right[i] == 0 || (left[i] == INT_MIN && right[i] == -1)) {
            return false;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        result[i] = left[i] % right[i];
    }

    return true;
}

int main(void)
{
    const int first[] = {10, 20, 30, 40};
    const int second[] = {3, 6, 7, 9};
    const size_t length = sizeof(first) / sizeof(first[0]);

    int *result = malloc(length * sizeof(*result));
    if (result == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!tuple_modulo(first, second, result, length)) {
        fputs("Modulo operation failed.\n", stderr);
        free(result);
        return EXIT_FAILURE;
    }

    putchar('(');
    for (size_t i = 0; i < length; ++i) {
        printf("%d%s", result[i], i + 1 < length ? ", " : "");
    }
    puts(")");

    free(result);
    return EXIT_SUCCESS;
}