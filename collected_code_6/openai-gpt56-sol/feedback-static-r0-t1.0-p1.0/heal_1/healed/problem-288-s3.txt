#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_prime(uint64_t value)
{
    uint64_t divisor;

    if (value < 2U) {
        return 0;
    }

    if (value % 2U == 0U) {
        return value == 2U;
    }

    for (divisor = 3U; divisor <= value / divisor; divisor += 2U) {
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

    do {
        ch = getchar();
        if (ch == EOF) {
            return 0;
        }
    } while (ch == ' ' || ch == '\t' || ch == '\n' ||
             ch == '\r' || ch == '\f' || ch == '\v');

    do {
        if (length + 1U >= capacity) {
            do {
                ch = getchar();
            } while (ch != EOF && ch != ' ' && ch != '\t' &&
                     ch != '\n' && ch != '\r' && ch != '\f' &&
                     ch != '\v');
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && ch != ' ' && ch != '\t' &&
             ch != '\n' && ch != '\r' && ch != '\f' &&
             ch != '\v');

    buffer[length] = '\0';
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char buffer[32];
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
    char buffer[32];
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

static size_t count_self_inverse_elements(const int64_t array[],
                                          size_t length,
                                          uint64_t modulus)
{
    size_t count = 0U;
    size_t index;

    for (index = 0U; index < length; ++index) {
        uint64_t residue;

        if (array[index] >= 0) {
            residue = (uint64_t)array[index] % modulus;
        } else {
            const uint64_t magnitude =
                (uint64_t)(-(array[index] + 1)) + UINT64_C(1);
            const uint64_t remainder = magnitude % modulus;

            residue = remainder == 0U ? 0U : modulus - remainder;
        }

        if (residue == 1U || residue == modulus - 1U) {
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

    if (length != 0U) {
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