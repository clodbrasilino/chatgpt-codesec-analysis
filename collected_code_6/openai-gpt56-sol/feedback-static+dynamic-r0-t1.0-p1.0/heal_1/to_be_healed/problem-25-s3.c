#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>

static int multiply_checked(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((right > 0 && (left > INT64_MAX / right || left < INT64_MIN / right)) ||
        (right < 0 && ((right == -1 && left == INT64_MIN) ||
                       (right != -1 &&
                        (left > INT64_MIN / right || left < INT64_MAX / right))))) {
        return 0;
    }

    *result = left * right;
    return 1;
}

static int product_of_non_repeated(const int64_t array[], size_t length,
                                   int64_t *product)
{
    int64_t result = 1;
    int found = 0;

    if ((array == NULL && length != 0U) || product == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        int repeated = 0;

        for (size_t j = 0; j < length; ++j) {
            if (i != j && array[i] == array[j]) {
                repeated = 1;
                break;
            }
        }

        if (!repeated) {
            if (!multiply_checked(result, array[i], &result)) {
                return 0;
            }
            found = 1;
        }
    }

    if (!found) {
        return 0;
    }

    *product = result;
    return 1;
}

int main(void)
{
    size_t length;
    int64_t *array = NULL;
    int64_t product;

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid array length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0U) {
        fputs("The array must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array size is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         */
        if (scanf("%" SCNd64, &array[i]) != 1) {
            fputs("Invalid array element.\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!product_of_non_repeated(array, length, &product)) {
        fputs("No unique elements or product overflow.\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", product);
    free(array);
    return EXIT_SUCCESS;
}