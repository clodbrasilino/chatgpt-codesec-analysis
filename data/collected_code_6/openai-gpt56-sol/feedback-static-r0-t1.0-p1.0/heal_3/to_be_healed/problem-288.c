#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_prime(uint64_t n)
{
    if (n < UINT64_C(2)) {
        return 0;
    }

    if (n % UINT64_C(2) == 0) {
        return n == UINT64_C(2);
    }

    for (uint64_t divisor = UINT64_C(3);
         divisor <= n / divisor;
         divisor += UINT64_C(2)) {
        if (n % divisor == 0) {
            return 0;
        }
    }

    return 1;
}

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && (ch == ' ' || ch == '\t' || ch == '\n' ||
                            ch == '\r' || ch == '\f' || ch == '\v'));

    if (ch == EOF) {
        return 0;
    }

    do {
        if (length + 1 >= size) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != EOF && ch != ' ' && ch != '\t' && ch != '\n' &&
                     ch != '\r' && ch != '\f' && ch != '\v');
            return 0;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != EOF && ch != ' ' && ch != '\t' && ch != '\n' &&
             ch != '\r' && ch != '\f' && ch != '\v');

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

    if (!read_token(buffer, sizeof(buffer)) || buffer[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
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

    if (!read_uint64(&parsed) || parsed > SIZE_MAX) {
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

    if (!read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static size_t count_self_inverse_elements(const int64_t *array,
                                          size_t length,
                                          uint64_t prime)
{
    size_t count = 0;

    for (size_t i = 0; i < length; ++i) {
        uint64_t residue;

        if (array[i] >= 0) {
            residue = (uint64_t)array[i] % prime;
        } else {
            uint64_t magnitude =
                (uint64_t)(-(array[i] + INT64_C(1))) + UINT64_C(1);
            uint64_t remainder = magnitude % prime;
            residue = remainder == 0 ? 0 : prime - remainder;
        }

        if (residue == UINT64_C(1) ||
            residue == prime - UINT64_C(1)) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    uint64_t prime;
    size_t length;
    int64_t *array = NULL;

    if (!read_uint64(&prime) || !read_size(&length) || !is_prime(prime)) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", count_self_inverse_elements(array, length, prime));

    free(array);
    return EXIT_SUCCESS;
}