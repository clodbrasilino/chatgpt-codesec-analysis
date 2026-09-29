#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static size_t max_subsequence_length(const int64_t *array, size_t length,
                                     int64_t difference)
{
    size_t best = 0;

    for (size_t i = 0; i < length; ++i) {
        size_t current = 1;
        /* Possible weaknesses found:
         *  Possible null pointer dereference: array [nullPointer]
         *  Null pointer dereference
         */
        int64_t value = array[i];

        for (size_t j = i + 1; j < length; ++j) {
            if ((difference > 0 && value <= INT64_MAX - difference &&
                 array[j] == value + difference) ||
                (difference < 0 && value >= INT64_MIN - difference &&
                 array[j] == value + difference) ||
                (difference == 0 && array[j] == value)) {
                value = array[j];
                ++current;
            }
        }

        if (current > best) {
            best = current;
        }
    }

    return best;
}

int main(void)
{
    size_t length = 0;
    int64_t difference = 0;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%zu %" SCNd64, &length, &difference) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int64_t)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Assignment 'array=NULL', assigned value is 0
     */
    int64_t *array = NULL;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < length; ++i) {
            /* Possible weaknesses found:
             * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
             */
            if (scanf("%" SCNd64, &array[i]) != 1) {
                fputs("Invalid input\n", stderr);
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    /* Possible weaknesses found:
     *  Calling function 'max_subsequence_length', 1st argument 'array' value is 0
     */
    printf("%zu\n", max_subsequence_length(array, length, difference));
    free(array);

    return EXIT_SUCCESS;
}