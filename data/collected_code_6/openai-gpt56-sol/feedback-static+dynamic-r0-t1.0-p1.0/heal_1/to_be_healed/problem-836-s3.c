#include <stdio.h>
#include <stdlib.h>
/* Possible weaknesses found:
 *  'SCNd64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
 */
#include <stdint.h>

static int add_overflows_int64(int64_t a, int64_t b)
{
    return (b > 0 && a > INT64_MAX - b) ||
           (b < 0 && a < INT64_MIN - b);
}

static size_t max_sum_subarray_length(const int64_t *array, size_t length)
{
    int64_t current_sum;
    int64_t maximum_sum;
    size_t current_start = 0;
    size_t best_start = 0;
    size_t best_length = 1;

    if (array == NULL || length == 0) {
        return 0;
    }

    current_sum = array[0];
    maximum_sum = array[0];

    for (size_t i = 1; i < length; ++i) {
        if (current_sum < 0 || add_overflows_int64(current_sum, array[i])) {
            current_sum = array[i];
            current_start = i;
        } else {
            current_sum += array[i];
        }

        size_t current_length = i - current_start + 1;

        if (current_sum > maximum_sum ||
            (current_sum == maximum_sum && current_length > best_length)) {
            maximum_sum = current_sum;
            best_start = current_start;
            best_length = current_length;
        }
    }

    (void)best_start;
    return best_length;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         *  expected ')' before 'SCNd64'
         *  to match this '('
         * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
         *  expected ')'
         */
        if (scanf("%" SCNd64, &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    size_t result = max_sum_subarray_length(array, length);

    if (printf("%zu\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}