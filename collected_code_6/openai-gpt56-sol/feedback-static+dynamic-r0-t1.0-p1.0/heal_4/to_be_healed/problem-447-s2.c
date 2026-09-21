#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

static int read_line(char **line)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length + 1) {
                new_capacity = length + 2;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF) {
        if (ferror(stdin) || length == 0) {
            free(buffer);
            return -1;
        }
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return -1;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int read_int64(int64_t *result)
{
    char *buffer;
    char *start;
    char *end;
    intmax_t value;

    if (result == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    value = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        value < INT64_MIN || value > INT64_MAX) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *result = (int64_t)value;
    free(buffer);
    return 0;
}

static int read_size(size_t *result)
{
    char *buffer;
    char *start;
    char *end;
    uintmax_t value;

    if (result == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || value == 0 || value > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    *result = (size_t)value;
    free(buffer);
    return 0;
}

static int cube_int64(int64_t value, int64_t *result)
{
    if (result == NULL ||
        value > INT64_C(2097151) ||
        value < -INT64_C(2097152)) {
        return -1;
    }

    *result = value * value * value;
    return 0;
}

int main(void)
{
    size_t count;
    int64_t *values;

    if (printf("Enter the number of elements: ") < 0 ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (read_size(&count) != 0 ||
        count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Invalid element count.\n");
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("Element %zu: ", i + 1) < 0 ||
            fflush(stdout) == EOF ||
            read_int64(&values[i]) != 0) {
            fprintf(stderr, "Invalid input.\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t cube;

        if (cube_int64(values[i], &cube) != 0) {
            fprintf(stderr,
                    "Cube of element %zu is outside the int64_t range.\n",
                    i + 1);
            free(values);
            return EXIT_FAILURE;
        }

        if (printf("%" PRId64 "%c", cube,
                   i + 1 == count ? '\n' : ' ') < 0) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    free(values);
    return EXIT_SUCCESS;
}