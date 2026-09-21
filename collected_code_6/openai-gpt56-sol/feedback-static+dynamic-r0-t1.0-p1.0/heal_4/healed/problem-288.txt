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
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int is_space_without_newline(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' ||
           ch == '\v' || ch == '\f';
}

static const char *skip_space(const char *text)
{
    while (is_space_without_newline(*text)) {
        ++text;
    }

    return text;
}

static int only_trailing_space(const char *text)
{
    return *skip_space(text) == '\0';
}

static int read_uint64(uint64_t *value)
{
    char *line;
    char *end;
    const char *start;
    uintmax_t parsed;
    int valid;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    start = skip_space(line);
    errno = 0;
    parsed = strtoumax(start, &end, 10);

    valid = *start != '-' &&
            end != start &&
            errno != ERANGE &&
            parsed <= UINT64_MAX &&
            only_trailing_space(end);

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
    const char *start;
    uintmax_t parsed;
    int valid;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    start = skip_space(line);
    errno = 0;
    parsed = strtoumax(start, &end, 10);

    valid = *start != '-' &&
            end != start &&
            errno != ERANGE &&
            parsed <= SIZE_MAX &&
            only_trailing_space(end);

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
    const char *start;
    intmax_t parsed;
    int valid;

    if (value == NULL || !read_line(&line)) {
        return 0;
    }

    start = skip_space(line);
    errno = 0;
    parsed = strtoimax(start, &end, 10);

    valid = end != start &&
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

static uint64_t positive_magnitude(int64_t value)
{
    return (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
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
            uint64_t remainder = positive_magnitude(array[i]) % prime;
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

    if (!is_prime(prime) || length > SIZE_MAX / sizeof(*array)) {
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

    if (printf("%zu\n",
               count_self_inverse_elements(array, length, prime)) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}