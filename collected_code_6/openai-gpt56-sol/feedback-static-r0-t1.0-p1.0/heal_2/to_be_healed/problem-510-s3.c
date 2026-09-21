#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static uint64_t add_saturating(uint64_t a, uint64_t b)
{
    return UINT64_MAX - a < b ? UINT64_MAX : a + b;
}

static uint64_t mul2_saturating(uint64_t value)
{
    return value > UINT64_MAX / 2U ? UINT64_MAX : value * 2U;
}

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];

    if (value == NULL || fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    char *start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed > UINT64_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static uint64_t count_subsequences_product_less_than_k(
    const uint64_t *array,
    size_t length,
    uint64_t k)
{
    if (array == NULL || length == 0U || k == 0U) {
        return 0U;
    }

    uint64_t zero_count = 0U;
    uint64_t positive_count = 0U;
    uint64_t total_without_zeros = 1U;

    for (size_t i = 0U; i < length; ++i) {
        if (array[i] == 0U) {
            zero_count = add_saturating(zero_count, total_without_zeros);
        } else {
            if (array[i] < k) {
                positive_count =
                    add_saturating(positive_count, total_without_zeros);
            }
            total_without_zeros = mul2_saturating(total_without_zeros);
            zero_count = mul2_saturating(zero_count);
        }
    }

    return add_saturating(zero_count, positive_count);
}

int main(void)
{
    uint64_t length_input;
    uint64_t k;

    if (!read_uint64(&length_input) || !read_uint64(&k)) {
        return EXIT_FAILURE;
    }

    if (length_input > SIZE_MAX ||
        length_input > SIZE_MAX / sizeof(uint64_t)) {
        return EXIT_FAILURE;
    }

    size_t length = (size_t)length_input;
    uint64_t *array = NULL;

    if (length != 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }

        for (size_t i = 0U; i < length; ++i) {
            if (!read_uint64(&array[i])) {
                free(array);
                return EXIT_FAILURE;
            }
        }
    }

    uint64_t result =
        count_subsequences_product_less_than_k(array, length, k);

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}