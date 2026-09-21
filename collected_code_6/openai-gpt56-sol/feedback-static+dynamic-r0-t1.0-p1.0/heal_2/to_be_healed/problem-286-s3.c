#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    do {
        if (length + 1 < size) {
            buffer[length++] = (char)ch;
        } else {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != EOF && !isspace((unsigned char)ch));
            return 0;
        }

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    return 1;
}

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];
    char *end;
    uintmax_t parsed;

    if (!read_token(buffer, sizeof(buffer)) || buffer[0] == '-') {
        return 0;
    }

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'errno'
     *  'errno' undeclared (first use in this function)
     */
    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    /* Possible weaknesses found:
     *  'ERANGE' undeclared (first use in this function)
     *  use of undeclared identifier 'errno'
     *  use of undeclared identifier 'ERANGE'
     */
    if (errno == ERANGE || *end != '\0' || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];
    char *end;
    intmax_t parsed;

    if (!read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    /* Possible weaknesses found:
     *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
     *  use of undeclared identifier 'errno'
     *  'errno' undeclared (first use in this function)
     */
    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    /* Possible weaknesses found:
     *  'ERANGE' undeclared (first use in this function)
     *  use of undeclared identifier 'errno'
     *  use of undeclared identifier 'ERANGE'
     */
    if (errno == ERANGE || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int64_t saturating_add(int64_t a, int64_t b)
{
    if (b > 0 && a > INT64_MAX - b) {
        return INT64_MAX;
    }

    if (b < 0 && a < INT64_MIN - b) {
        return INT64_MIN;
    }

    return a + b;
}

static int64_t saturating_multiply_positive(int64_t value, uint64_t factor)
{
    if (value <= 0 || factor == 0) {
        return 0;
    }

    if (factor > (uint64_t)INT64_MAX ||
        value > INT64_MAX / (int64_t)factor) {
        return INT64_MAX;
    }

    return value * (int64_t)factor;
}

static int64_t max_subarray_repeated(const int64_t *array, size_t length,
                                     uint64_t repetitions)
{
    int64_t total = 0;
    int64_t prefix = INT64_MIN;
    int64_t suffix = INT64_MIN;
    int64_t best = INT64_MIN;
    int64_t running_prefix = 0;
    int64_t running_suffix = 0;
    int64_t current = INT64_MIN;

    for (size_t i = 0; i < length; ++i) {
        total = saturating_add(total, array[i]);
        running_prefix = saturating_add(running_prefix, array[i]);

        if (running_prefix > prefix) {
            prefix = running_prefix;
        }

        current = current < 0
                      ? array[i]
                      : saturating_add(current, array[i]);

        if (current > best) {
            best = current;
        }
    }

    for (size_t i = length; i > 0; --i) {
        running_suffix = saturating_add(running_suffix, array[i - 1]);

        if (running_suffix > suffix) {
            suffix = running_suffix;
        }
    }

    if (repetitions == 1) {
        return best;
    }

    int64_t spanning = saturating_add(suffix, prefix);

    if (repetitions > 2 && total > 0) {
        int64_t middle_sum =
            saturating_multiply_positive(total, repetitions - 2);
        spanning = saturating_add(spanning, middle_sum);
    }

    return best > spanning ? best : spanning;
}

int main(void)
{
    uint64_t input_length;
    uint64_t repetitions;

    if (!read_uint64(&input_length) ||
        !read_uint64(&repetitions) ||
        input_length == 0 ||
        repetitions == 0 ||
        input_length > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = (size_t)input_length;
    int64_t *array = malloc(length * sizeof(*array));

    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    int64_t result = max_subarray_repeated(array, length, repetitions);
    printf("%" PRId64 "\n", result);

    free(array);
    return EXIT_SUCCESS;
}