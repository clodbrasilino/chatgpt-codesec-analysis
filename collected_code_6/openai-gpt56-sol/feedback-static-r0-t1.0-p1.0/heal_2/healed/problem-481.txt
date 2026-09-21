#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static bool has_subset_sum(const int *values, size_t count, size_t target, bool *result)
{
    if (result == NULL) {
        return false;
    }

    *result = false;

    if (target == 0U) {
        *result = true;
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

        for (size_t sum = target;; --sum) {
            if (sum < value) {
                break;
            }

            if (reachable[sum - value]) {
                reachable[sum] = true;
            }

            if (sum == value) {
                break;
            }
        }

        if (reachable[target]) {
            *result = true;
            free(reachable);
            return true;
        }
    }

    *result = reachable[target];
    free(reachable);
    return true;
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
        if (*capacity - length < 2U) {
            if (length > SIZE_MAX - 2U) {
                free(*line);
                *line = NULL;
                *capacity = 0U;
                return false;
            }

            size_t minimum = length + 2U;
            size_t new_capacity = *capacity == 0U ? 64U : *capacity;

            if (new_capacity < minimum) {
                if (new_capacity > SIZE_MAX / 2U) {
                    new_capacity = minimum;
                } else {
                    new_capacity *= 2U;
                    if (new_capacity < minimum) {
                        new_capacity = minimum;
                    }
                }
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

        size_t available = *capacity - length;

        if (available > (size_t)INT_MAX) {
            available = (size_t)INT_MAX;
        }

        if (fgets(*line + length, (int)available, stdin) == NULL) {
            if (ferror(stdin) || length == 0U) {
                free(*line);
                *line = NULL;
                *capacity = 0U;
                return false;
            }

            (*line)[length] = '\0';
            return true;
        }

        size_t added = 0U;
        while (added + 1U < available &&
               (*line)[length + added] != '\0' &&
               (*line)[length + added] != '\n') {
            ++added;
        }

        if ((*line)[length + added] == '\n') {
            (*line)[length + added] = '\0';
            return true;
        }

        length += added;

        if (feof(stdin)) {
            (*line)[length] = '\0';
            return true;
        }
    }
}

static bool parse_size(const char *text, size_t *result)
{
    if (text == NULL || result == NULL) {
        return false;
    }

    const unsigned char *cursor = (const unsigned char *)text;

    while (isspace(*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '-' || *cursor == '+') {
        return false;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long value = strtoull((const char *)cursor, &end, 10);

    if (errno == ERANGE || end == (const char *)cursor) {
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || value > SIZE_MAX) {
        return false;
    }

    *result = (size_t)value;
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

    bool valid = parse_size(line, result);
    free(line);
    return valid;
}

static bool parse_values(const char *text, int *values, size_t count)
{
    if (text == NULL || (count > 0U && values == NULL)) {
        return false;
    }

    const char *cursor = text;

    for (size_t i = 0U; i < count; ++i) {
        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor == '\0' || *cursor == '-' || *cursor == '+') {
            return false;
        }

        errno = 0;
        char *end = NULL;
        unsigned long value = strtoul(cursor, &end, 10);

        if (errno == ERANGE || end == cursor || value > (unsigned long)INT_MAX) {
            return false;
        }

        values[i] = (int)value;
        cursor = end;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    return *cursor == '\0';
}

static bool read_values(int *values, size_t count)
{
    if (count > 0U && values == NULL) {
        return false;
    }

    if (fputs("Enter the nonnegative elements: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return false;
    }

    char *line = NULL;
    size_t capacity = 0U;

    if (!read_line(&line, &capacity)) {
        return false;
    }

    bool valid = parse_values(line, values, count);
    free(line);
    return valid;
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

    if (!read_values(values, count)) {
        fputs("Invalid element list.\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (!read_size("Enter the target sum: ", &target)) {
        fputs("Invalid target sum.\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    bool found = false;

    if (!has_subset_sum(values, count, target, &found)) {
        fputs("Unable to compute the subset sum.\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    puts(found
             ? "A subset with the target sum exists."
             : "No subset with the target sum exists.");

    free(values);
    return EXIT_SUCCESS;
}