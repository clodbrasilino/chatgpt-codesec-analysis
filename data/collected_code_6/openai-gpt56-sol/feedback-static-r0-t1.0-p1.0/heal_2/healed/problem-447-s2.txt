#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int read_line(char **buffer, size_t *capacity)
{
    if (buffer == NULL || capacity == NULL) {
        return -1;
    }

    size_t length = 0;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            return -1;
        }

        if (length + 1 >= *capacity) {
            size_t new_capacity = *capacity == 0 ? 64 : *capacity;

            if (new_capacity > SIZE_MAX / 2) {
                return -1;
            }

            new_capacity *= 2;
            char *new_buffer = realloc(*buffer, new_capacity);

            if (new_buffer == NULL) {
                return -1;
            }

            *buffer = new_buffer;
            *capacity = new_capacity;
        }

        (*buffer)[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        return -1;
    }

    if (length + 1 > *capacity) {
        size_t new_capacity = length + 1;
        char *new_buffer = realloc(*buffer, new_capacity);

        if (new_buffer == NULL) {
            return -1;
        }

        *buffer = new_buffer;
        *capacity = new_capacity;
    }

    (*buffer)[length] = '\0';
    return 0;
}

static int parse_size(const char *text, size_t *result)
{
    if (text == NULL || result == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    if (*text == '\0' || *text == '-' || *text == '+') {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || value > SIZE_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *result = (size_t)value;
    return 0;
}

static int parse_int64(const char *text, int64_t *result)
{
    if (text == NULL || result == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    if (*text == '\0') {
        return -1;
    }

    errno = 0;
    char *end = NULL;
    intmax_t value = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text ||
        value < INT64_MIN || value > INT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *result = (int64_t)value;
    return 0;
}

static int cube_int64(int64_t value, int64_t *result)
{
    if (result == NULL ||
        value < INT64_C(-2097152) ||
        value > INT64_C(2097151)) {
        return -1;
    }

    *result = value * value * value;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t input_capacity = 0;
    size_t count;

    if (printf("Enter the number of elements: ") < 0 ||
        fflush(stdout) == EOF ||
        read_line(&input, &input_capacity) != 0 ||
        parse_size(input, &count) != 0 ||
        count == 0 ||
        count > SIZE_MAX / sizeof(int64_t)) {
        fprintf(stderr, "Invalid element count.\n");
        free(input);
        return EXIT_FAILURE;
    }

    int64_t *values = malloc(count * sizeof(*values));

    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(input);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("Element %zu: ", i + 1) < 0 ||
            fflush(stdout) == EOF ||
            read_line(&input, &input_capacity) != 0 ||
            parse_int64(input, &values[i]) != 0) {
            fprintf(stderr, "Invalid input.\n");
            free(values);
            free(input);
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
            free(input);
            return EXIT_FAILURE;
        }

        if (printf("%" PRId64 "%c",
                   cube, i + 1 == count ? '\n' : ' ') < 0) {
            free(values);
            free(input);
            return EXIT_FAILURE;
        }
    }

    free(values);
    free(input);
    return EXIT_SUCCESS;
}