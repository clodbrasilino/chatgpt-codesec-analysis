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

    if (values == NULL || target == SIZE_MAX) {
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

static bool read_line(char **line, size_t *capacity)
{
    if (line == NULL || capacity == NULL) {
        return false;
    }

    if ((*line == NULL && *capacity != 0U) ||
        (*line != NULL && *capacity == 0U)) {
        return false;
    }

    size_t length = 0U;

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0U) {
                free(*line);
                *line = NULL;
                *capacity = 0U;
                return false;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2U) {
            free(*line);
            *line = NULL;
            *capacity = 0U;
            return false;
        }

        size_t required = length + 2U;

        if (required > *capacity) {
            size_t new_capacity = *capacity == 0U ? 64U : *capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2U) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2U;
            }

            char *new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                free(*line);
                *line = NULL;
                *capacity = 0U;
                return false;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (*capacity <= length) {
        size_t required = length + 1U;
        char *new_line = realloc(*line, required);

        if (new_line == NULL) {
            free(*line);
            *line = NULL;
            *capacity = 0U;
            return false;
        }

        *line = new_line;
        *capacity = required;
    }

    (*line)[length] = '\0';
    return true;
}

static bool read_size(const char *prompt, size_t *result)
{
    if (prompt == NULL || result == NULL) {
        return false;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return false;
    }

    char *line = NULL;
    size_t capacity = 0U;

    if (!read_line(&line, &capacity)) {
        return false;
    }

    char *start = line;
    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '-' || *start == '+' || *start == '\0') {
        free(line);
        return false;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(line);
        return false;
    }

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0' || value > (uintmax_t)SIZE_MAX) {
        free(line);
        return false;
    }

    *result = (size_t)value;
    free(line);
    return true;
}

static bool read_nonnegative_int(const char *prompt, int *result)
{
    if (prompt == NULL || result == NULL) {
        return false;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return false;
    }

    char *line = NULL;
    size_t capacity = 0U;

    if (!read_line(&line, &capacity)) {
        return false;
    }

    char *start = line;
    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '-' || *start == '+' || *start == '\0') {
        free(line);
        return false;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value > (uintmax_t)INT_MAX) {
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

    *result = (int)value;
    free(line);
    return true;
}

int main(void)
{
    size_t count = 0U;
    size_t target = 0U;

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

    if (puts(found
                 ? "A subset with the target sum exists."
                 : "No subset with the target sum exists.") == EOF) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}