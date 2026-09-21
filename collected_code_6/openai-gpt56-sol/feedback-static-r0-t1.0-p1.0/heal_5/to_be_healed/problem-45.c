#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t magnitude(int64_t value)
{
    uint64_t converted = (uint64_t)value;
    return value < 0 ? UINT64_C(0) - converted : converted;
}

static uint64_t gcd_pair(uint64_t a, uint64_t b)
{
    while (b != 0) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    int ch;
    char *buffer;

    if (line == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static char *skip_whitespace(char *text)
{
    while (*text == ' ' || *text == '\t' || *text == '\r' ||
           *text == '\n' || *text == '\f' || *text == '\v') {
        ++text;
    }

    return text;
}

static int read_size(size_t *value)
{
    char *buffer;
    char *start;
    char *end;
    uintmax_t parsed;
    int status = -1;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = skip_whitespace(buffer);

    if (*start == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end != start && errno != ERANGE && parsed != 0 &&
        parsed <= (uintmax_t)SIZE_MAX &&
        *skip_whitespace(end) == '\0') {
        *value = (size_t)parsed;
        status = 0;
    }

    free(buffer);
    return status;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *start;
    char *end;
    intmax_t parsed;
    int status = -1;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = skip_whitespace(buffer);
    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (end != start && errno != ERANGE &&
        parsed >= INT64_MIN && parsed <= INT64_MAX &&
        *skip_whitespace(end) == '\0') {
        *value = (int64_t)parsed;
        status = 0;
    }

    free(buffer);
    return status;
}

int main(void)
{
    size_t count;
    uint64_t result = 0;

    if (read_size(&count) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t value;

        if (read_int64(&value) != 0) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        result = gcd_pair(result, magnitude(value));
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}