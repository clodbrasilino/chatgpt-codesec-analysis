#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_difference_of_two_squares(int64_t number)
{
    uint64_t magnitude;

    if (number < 0) {
        magnitude = (uint64_t)(-(number + INT64_C(1))) + UINT64_C(1);
    } else {
        magnitude = (uint64_t)number;
    }

    return magnitude % UINT64_C(4) != UINT64_C(2);
}

static bool is_space_character(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static bool read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (line == NULL || capacity == NULL) {
        return false;
    }

    *line = NULL;
    *capacity = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        char *resized;

        if (length + 1 >= *capacity) {
            size_t new_capacity = *capacity == 0 ? 64 : *capacity * 2;

            if (new_capacity <= *capacity) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                return false;
            }

            resized = realloc(*line, new_capacity);
            if (resized == NULL) {
                free(*line);
                *line = NULL;
                *capacity = 0;
                return false;
            }

            *line = resized;
            *capacity = new_capacity;
        }

        if (ch == '\n') {
            break;
        }

        (*line)[length++] = (char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        free(*line);
        *line = NULL;
        *capacity = 0;
        return false;
    }

    if (length + 1 >= *capacity) {
        char *resized;
        size_t new_capacity = *capacity == 0 ? 2 : *capacity + 1;

        resized = realloc(*line, new_capacity);
        if (resized == NULL) {
            free(*line);
            *line = NULL;
            *capacity = 0;
            return false;
        }

        *line = resized;
        *capacity = new_capacity;
    }

    (*line)[length] = '\0';
    return true;
}

static bool read_int64(int64_t *result)
{
    char *line;
    size_t capacity;
    char *start;
    char *end;
    intmax_t value;
    int ch;

    if (result == NULL || !read_line(&line, &capacity)) {
        return false;
    }

    start = line;
    while (is_space_character((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        free(line);
        return false;
    }

    errno = 0;
    value = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        value < INT64_MIN || value > INT64_MAX) {
        free(line);
        return false;
    }

    while (is_space_character((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return false;
    }

    free(line);

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (!is_space_character(ch)) {
            return false;
        }
    }

    if (ferror(stdin)) {
        return false;
    }

    *result = (int64_t)value;
    return true;
}

int main(void)
{
    int64_t value;

    if (!read_int64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_difference_of_two_squares(value) ? "Yes" : "No");
    return EXIT_SUCCESS;
}