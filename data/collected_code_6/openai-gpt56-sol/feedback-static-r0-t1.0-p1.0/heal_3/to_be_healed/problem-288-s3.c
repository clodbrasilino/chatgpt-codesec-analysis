#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_space(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int is_prime(uint64_t value)
{
    uint64_t divisor;

    if (value < UINT64_C(2)) {
        return 0;
    }

    if (value % UINT64_C(2) == 0U) {
        return value == UINT64_C(2);
    }

    for (divisor = UINT64_C(3);
         divisor <= value / divisor;
         divisor += UINT64_C(2)) {
        if (value % divisor == 0U) {
            return 0;
        }
    }

    return 1;
}

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0U;

    if (buffer == NULL || capacity == 0U) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (is_space(ch));

    while (ch != EOF && !is_space(ch)) {
        if (length >= capacity - 1U) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != EOF && !is_space(ch));

            buffer[0] = '\0';
            return 0;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        buffer[0] = '\0';
        return 0;
    }

    buffer[length] = '\0';
    return 1;
}

static int read_uint64(uint64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer)) ||
        buffer[0] == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int read_size(size_t *value)
{
    uint64_t parsed;

    if (value == NULL || !read_uint64(&parsed) ||
        parsed > (uint64_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static uint64_t normalized_residue(int64_t value, uint64_t modulus)
{
    if (value >= 0) {
        return (uint64_t)value % modulus;
    }

    {
        uint64_t magnitude = (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
        uint64_t remainder = magnitude % modulus;

        return remainder == 0U ? 0U : modulus - remainder;
    }
}

static size_t count_self_inverse_elements(const int64_t *array,
                                          size_t length,
                                          uint64_t modulus)
{
    size_t count = 0U;
    size_t index;

    for (index = 0U; index < length; ++index) {
        uint64_t residue = normalized_residue(array[index], modulus);

        if (residue == UINT64_C(1) ||
            residue == modulus - UINT64_C(1)) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    size_t length;
    uint64_t modulus;
    int64_t *array = NULL;
    size_t index;
    size_t count;

    if (!read_size(&length) || !read_uint64(&modulus)) {
        return EXIT_FAILURE;
    }

    if (!is_prime(modulus) || length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length > 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (index = 0U; index < length; ++index) {
        if (!read_int64(&array[index])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    count = count_self_inverse_elements(array, length, modulus);

    if (printf("%zu\n", count) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}