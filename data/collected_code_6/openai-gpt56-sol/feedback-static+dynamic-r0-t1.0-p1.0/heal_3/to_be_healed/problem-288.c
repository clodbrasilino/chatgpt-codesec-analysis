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

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    int ch;

    *line = malloc(capacity);
    if (*line == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                free(*line);
                *line = NULL;
                return 0;
            }

            new_capacity = capacity * 2;
            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                free(*line);
                *line = NULL;
                return 0;
            }

            *line = new_line;
            capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(*line);
        *line = NULL;
        return 0;
    }

    (*line)[length] = '\0';
    return 1;
}

static int only_trailing_space(const char *text)
{
    while (*text == ' ' || *text == '\t' ||
           *text == '\r' || *text == '\v' || *text == '\f') {
        ++text;
    }

    return *text == '\0';
}

static int read_uint64(uint64_t *value)
{
    char *line;
    char *end;
    uintmax_t parsed;
    int valid;

    if (!read_line(&line)) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);
    valid = end != line &&
            errno != ERANGE &&
            parsed <= UINT64_MAX &&
            only_trailing_space(end);

    if (valid) {
        const char *p = line;

        while (*p == ' ' || *p == '\t' ||
               *p == '\r' || *p == '\v' || *p == '\f') {
            ++p;
        }

        if (*p == '-') {
            valid = 0;
        }
    }

    if (valid) {
        *value = (uint64_t)parsed;
    }

    free(line);
    return valid;
}

static int read_size(size_t *value)
{
    char *line;
    char *end;
    uintmax_t parsed;
    int valid;

    if (!read_line(&line)) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);
    valid = end != line &&
            errno != ERANGE &&
            parsed <= SIZE_MAX &&
            only_trailing_space(end);

    if (valid) {
        const char *p = line;

        while (*p == ' ' || *p == '\t' ||
               *p == '\r' || *p == '\v' || *p == '\f') {
            ++p;
        }

        if (*p == '-') {
            valid = 0;
        }
    }

    if (valid) {
        *value = (size_t)parsed;
    }

    free(line);
    return valid;
}

static int read_int64(int64_t *value)
{
    char *line;
    char *end;
    intmax_t parsed;
    int valid;

    if (!read_line(&line)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(line, &end, 10);
    valid = end != line &&
            errno != ERANGE &&
            parsed >= INT64_MIN &&
            parsed <= INT64_MAX &&
            only_trailing_space(end);

    if (valid) {
        *value = (int64_t)parsed;
    }

    free(line);
    return valid;
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

    if (!read_uint64(&prime) || !read_size(&length)) {
        return EXIT_FAILURE;
    }

    if (!is_prime(prime) ||
        length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length > 0) {
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

    printf("%zu\n",
           count_self_inverse_elements(array, length, prime));

    free(array);
    return EXIT_SUCCESS;
}