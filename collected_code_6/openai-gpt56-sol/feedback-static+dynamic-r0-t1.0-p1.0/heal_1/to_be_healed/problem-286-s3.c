#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    return scanf("%" SCNd64, value) == 1;
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

        if (current < 0) {
            current = array[i];
        } else {
            current = saturating_add(current, array[i]);
        }
        if (current > best) {
            best = current;
        }
    }

    for (size_t i = length; i-- > 0;) {
        running_suffix = saturating_add(running_suffix, array[i]);
        if (running_suffix > suffix) {
            suffix = running_suffix;
        }
    }

    if (repetitions == 1) {
        return best;
    }

    int64_t spanning = saturating_add(suffix, prefix);

    if (repetitions > 2 && total > 0) {
        uint64_t middle_count = repetitions - 2;
        int64_t middle_sum;

        if (middle_count > (uint64_t)INT64_MAX ||
            total > INT64_MAX / (int64_t)middle_count) {
            middle_sum = INT64_MAX;
        } else {
            middle_sum = total * (int64_t)middle_count;
        }

        spanning = saturating_add(spanning, middle_sum);
    }

    return best > spanning ? best : spanning;
}

int main(void)
{
    uint64_t input_length;
    uint64_t repetitions;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64 " %" SCNu64, &input_length, &repetitions) != 2 ||
        input_length == 0 || repetitions == 0 ||
        input_length > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = (size_t)input_length;
    errno = 0;
    int64_t *array = malloc(length * sizeof(*array));

    if (array == NULL) {
        perror("malloc");
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