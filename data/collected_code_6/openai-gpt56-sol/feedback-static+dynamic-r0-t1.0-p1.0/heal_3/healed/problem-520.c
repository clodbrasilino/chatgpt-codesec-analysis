#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t gcd_uint64(uint64_t a, uint64_t b)
{
    while (b != UINT64_C(0)) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm_array(const uint64_t values[], size_t count, uint64_t *result)
{
    if (values == NULL || result == NULL || count == 0U) {
        return -1;
    }

    uint64_t current = UINT64_C(1);

    for (size_t i = 0U; i < count; ++i) {
        if (values[i] == UINT64_C(0)) {
            *result = UINT64_C(0);
            return 0;
        }

        uint64_t quotient = current / gcd_uint64(current, values[i]);

        if (quotient > UINT64_MAX / values[i]) {
            return -1;
        }

        current = quotient * values[i];
    }

    *result = current;
    return 0;
}

static int read_line(FILE *stream, char **line)
{
    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;

    size_t capacity = 64U;
    size_t length = 0U;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0U) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(buffer);
            return -1;
        }

        if (length + 1U >= capacity) {
            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            size_t new_capacity = capacity * 2U;
            char *resized = realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int parse_uintmax(const char *text, uintmax_t maximum,
                         int allow_zero, uintmax_t *value)
{
    if (text == NULL || value == NULL) {
        return -1;
    }

    const unsigned char *cursor = (const unsigned char *)text;

    while (isspace((int)*cursor) != 0) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax((const char *)cursor, &end, 10);

    if (errno == ERANGE || end == (const char *)cursor || parsed > maximum) {
        return -1;
    }

    cursor = (const unsigned char *)end;

    while (isspace((int)*cursor) != 0) {
        ++cursor;
    }

    if (*cursor != '\0' || (!allow_zero && parsed == UINTMAX_C(0))) {
        return -1;
    }

    *value = parsed;
    return 0;
}

static int read_size(size_t *value)
{
    if (value == NULL) {
        return -1;
    }

    char *line = NULL;

    if (read_line(stdin, &line) != 0) {
        return -1;
    }

    uintmax_t parsed = UINTMAX_C(0);
    int status = parse_uintmax(line, (uintmax_t)SIZE_MAX, 0, &parsed);
    free(line);

    if (status != 0) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_uint64(uint64_t *value)
{
    if (value == NULL) {
        return -1;
    }

    char *line = NULL;

    if (read_line(stdin, &line) != 0) {
        return -1;
    }

    uintmax_t parsed = UINTMAX_C(0);
    int status = parse_uintmax(line, (uintmax_t)UINT64_MAX, 1, &parsed);
    free(line);

    if (status != 0) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(void)
{
    size_t count = 0U;

    if (read_size(&count) != 0 ||
        count > SIZE_MAX / sizeof(uint64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t *values = malloc(count * sizeof(*values));

    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (read_uint64(&values[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    uint64_t result = UINT64_C(0);

    if (lcm_array(values, count, &result) != 0) {
        fputs("LCM overflow\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}