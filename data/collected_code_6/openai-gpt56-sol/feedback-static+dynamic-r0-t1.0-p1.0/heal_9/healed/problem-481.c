#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static bool has_subset_sum(const int *values, size_t count, size_t target)
{
    if (target == 0U) {
        return true;
    }

    if (values == NULL || target == SIZE_MAX ||
        target > (SIZE_MAX / sizeof(bool)) - 1U) {
        return false;
    }

    bool *reachable = calloc(target + 1U, sizeof(*reachable));
    if (reachable == NULL) {
        return false;
    }

    reachable[0] = true;

    for (size_t i = 0U; i < count; ++i) {
        if (values[i] < 0) {
            free(reachable);
            return false;
        }

        size_t value = (size_t)values[i];

        if (value == 0U || value > target) {
            continue;
        }

        for (size_t sum = target; sum >= value; --sum) {
            if (reachable[sum - value]) {
                reachable[sum] = true;
            }

            if (sum == value) {
                break;
            }
        }

        if (reachable[target]) {
            free(reachable);
            return true;
        }
    }

    bool result = reachable[target];
    free(reachable);
    return result;
}

static bool grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    if (buffer == NULL || capacity == NULL || required == 0U) {
        return false;
    }

    if ((*buffer == NULL) != (*capacity == 0U)) {
        return false;
    }

    if (required <= *capacity) {
        return true;
    }

    size_t new_capacity = *capacity == 0U ? 256U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2U;
    }

    char *new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return false;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return true;
}

static bool append_character(char **buffer, size_t *length, size_t *capacity,
                             char character)
{
    if (buffer == NULL || length == NULL || capacity == NULL ||
        *length == SIZE_MAX) {
        return false;
    }

    size_t required = *length + 1U;

    if (!grow_buffer(buffer, capacity, required)) {
        return false;
    }

    (*buffer)[*length] = character;
    *length = required;
    return true;
}

static bool read_line(FILE *stream, char **line, size_t *capacity)
{
    if (stream == NULL || line == NULL || capacity == NULL ||
        ((*line == NULL) != (*capacity == 0U))) {
        return false;
    }

    size_t length = 0U;

    for (;;) {
        int character = fgetc(stream);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stream) != 0 || length == 0U) {
                free(*line);
                *line = NULL;
                *capacity = 0U;
                return false;
            }

            break;
        }

        if (!append_character(line, &length, capacity, (char)character)) {
            free(*line);
            *line = NULL;
            *capacity = 0U;
            return false;
        }
    }

    if (!append_character(line, &length, capacity, '\0')) {
        free(*line);
        *line = NULL;
        *capacity = 0U;
        return false;
    }

    return true;
}

static bool read_uintmax(const char *prompt, uintmax_t maximum,
                         uintmax_t *result)
{
    if (prompt == NULL || result == NULL) {
        return false;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return false;
    }

    char *line = NULL;
    size_t capacity = 0U;

    if (!read_line(stdin, &line, &capacity)) {
        return false;
    }

    char *start = line;

    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        free(line);
        return false;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value > maximum) {
        free(line);
        return false;
    }

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return false;
    }

    *result = value;
    free(line);
    return true;
}

static bool read_size(const char *prompt, size_t *result)
{
    if (result == NULL) {
        return false;
    }

    uintmax_t value;

    if (!read_uintmax(prompt, (uintmax_t)SIZE_MAX, &value)) {
        return false;
    }

    *result = (size_t)value;
    return true;
}

static bool read_nonnegative_int(const char *prompt, int *result)
{
    if (result == NULL) {
        return false;
    }

    uintmax_t value;

    if (!read_uintmax(prompt, (uintmax_t)INT_MAX, &value)) {
        return false;
    }

    *result = (int)value;
    return true;
}

int main(void)
{
    size_t count;
    size_t target;

    if (!read_size("Enter the number of elements: ", &count)) {
        fputs("Invalid element count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        fputs("Element count is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    int *values = NULL;

    if (count != 0U) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        if (!read_nonnegative_int("Enter a nonnegative element: ", &values[i])) {
            fputs("Invalid element.\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!read_size("Enter the target sum: ", &target)) {
        fputs("Invalid target sum.\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    bool found = has_subset_sum(values, count, target);
    int status = puts(found
        ? "A subset with the target sum exists."
        : "No subset with the target sum exists.");

    free(values);
    return status == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}