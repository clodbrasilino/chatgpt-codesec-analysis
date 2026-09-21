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

    if (value % UINT64_C(2) == 0) {
        return value == UINT64_C(2);
    }

    for (divisor = UINT64_C(3);
         divisor <= value / divisor;
         divisor += UINT64_C(2)) {
        if (value % divisor == 0) {
            return 0;
        }
    }

    return 1;
}

static int read_token(char **token)
{
    char *buffer;
    size_t capacity = 32U;
    size_t length = 0U;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (is_space(ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (ch != EOF && !is_space(ch)) {
        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char *buffer;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '-' || buffer[0] == '\0') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > UINT64_MAX) {
        free(buffer);
        return 0;
    }

    *value = (uint64_t)parsed;
    free(buffer);
    return 1;
}

static int read_size(size_t *value)
{
    uint64_t parsed;

    if (value == NULL || !read_uint64(&parsed)) {
        return 0;
    }

#if SIZE_MAX < UINT64_MAX
    if (parsed > (uint64_t)SIZE_MAX) {
        return 0;
    }
#endif

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return 0;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 1;
}

static uint64_t normalized_residue(int64_t value, uint64_t modulus)
{
    if (value >= 0) {
        return (uint64_t)value % modulus;
    }

    {
        uint64_t magnitude =
            (uint64_t)(-(value + INT64_C(1))) + UINT64_C(1);
        uint64_t remainder = magnitude % modulus;

        return remainder == UINT64_C(0)
                   ? UINT64_C(0)
                   : modulus - remainder;
    }
}

int main(void)
{
    size_t length;
    uint64_t modulus;
    size_t index;
    size_t count = 0U;

    if (!read_size(&length) ||
        !read_uint64(&modulus) ||
        !is_prime(modulus)) {
        return EXIT_FAILURE;
    }

    for (index = 0U; index < length; ++index) {
        int64_t value;
        uint64_t residue;

        if (!read_int64(&value)) {
            return EXIT_FAILURE;
        }

        residue = normalized_residue(value, modulus);

        if (residue == UINT64_C(1) ||
            residue == modulus - UINT64_C(1)) {
            ++count;
        }
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}