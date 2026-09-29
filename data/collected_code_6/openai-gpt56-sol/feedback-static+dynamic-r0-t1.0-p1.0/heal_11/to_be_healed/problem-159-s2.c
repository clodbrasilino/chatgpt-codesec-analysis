#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_INPUT_LENGTH = 1024 };

static int is_valid_date(int month, int day)
{
    static const int days_in_month[] = {
        31, 29, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    return month >= 1 && month <= 12 &&
           day >= 1 && day <= days_in_month[month - 1];
}

static const char *get_season(int month, int day)
{
    int date = month * 100 + day;

    if (date >= 1221 || date < 320) {
        return "Winter";
    }

    if (date < 621) {
        return "Spring";
    }

    if (date < 923) {
        return "Summer";
    }

    return "Autumn";
}

static int parse_integer(const char **input, int *value)
{
    char *end;
    long result;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    if (**input == '\0') {
        return 0;
    }

    errno = 0;
    result = strtol(*input, &end, 10);

    if (end == *input || errno == ERANGE ||
        result < INT_MIN || result > INT_MAX) {
        return 0;
    }

    *value = (int)result;
    *input = end;
    return 1;
}

static int discard_line(FILE *stream)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stream) != NULL) {
        if (strchr(buffer, '\n') != NULL) {
            return 1;
        }
    }

    return feof(stream) ? 1 : 0;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer;
    char *newline;
    size_t length;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;

    buffer = malloc((size_t)MAX_INPUT_LENGTH + 2U);
    if (buffer == NULL) {
        return 0;
    }

    if (fgets(buffer, MAX_INPUT_LENGTH + 2, stream) == NULL) {
        free(buffer);
        return 0;
    }

    newline = strchr(buffer, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        length = strlen(buffer);

        if (length > MAX_INPUT_LENGTH) {
            if (!discard_line(stream)) {
                free(buffer);
                return 0;
            }

            free(buffer);
            return 0;
        }

        if (!feof(stream)) {
            if (!discard_line(stream)) {
                free(buffer);
                return 0;
            }

            free(buffer);
            return 0;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(buffer);

    if (length > 0U && buffer[length - 1U] == '\r') {
        buffer[length - 1U] = '\0';
    }

    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    const char *cursor;
    int month;
    int day;

    fputs("Enter month and day: ", stdout);

    if (fflush(stdout) == EOF || !read_line(stdin, &input)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_integer(&cursor, &month) ||
        !parse_integer(&cursor, &day)) {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!is_valid_date(month, day)) {
        fputs("Invalid date.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(get_season(month, day));
    return EXIT_SUCCESS;
}