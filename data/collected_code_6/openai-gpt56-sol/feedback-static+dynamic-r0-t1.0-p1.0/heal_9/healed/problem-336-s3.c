#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024U

static bool equals_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return false;
    }

    while (*left != '\0' && *right != '\0') {
        unsigned char left_char = (unsigned char)*left;
        unsigned char right_char = (unsigned char)*right;

        if (tolower(left_char) != tolower(right_char)) {
            return false;
        }

        ++left;
        ++right;
    }

    return *left == '\0' && *right == '\0';
}

static bool month_has_28_days(const char *month)
{
    return equals_ignore_case(month, "February");
}

static bool discard_line(FILE *stream)
{
    if (stream == NULL) {
        return false;
    }

    int character;

    do {
        character = fgetc(stream);
    } while (character != '\n' && character != EOF);

    return character == '\n' || feof(stream);
}

static char *read_line(FILE *stream)
{
    if (stream == NULL) {
        return NULL;
    }

    char *line = malloc(MAX_INPUT_LENGTH + 1U);
    if (line == NULL) {
        return NULL;
    }

    if (fgets(line, (int)(MAX_INPUT_LENGTH + 1U), stream) == NULL) {
        free(line);
        return NULL;
    }

    size_t length = strcspn(line, "\r\n");

    if (line[length] == '\r') {
        line[length] = '\0';

        int character = fgetc(stream);
        if (character != '\n' && character != EOF) {
            discard_line(stream);
            free(line);
            return NULL;
        }
    } else if (line[length] == '\n') {
        line[length] = '\0';
    } else {
        int character = fgetc(stream);

        if (character != '\n' && character != EOF) {
            discard_line(stream);
            free(line);
            return NULL;
        }
    }

    char *resized = realloc(line, length + 1U);
    return resized != NULL ? resized : line;
}

int main(void)
{
    char *month = read_line(stdin);

    if (month == NULL) {
        fputs("Failed to read the month name.\n", stderr);
        return EXIT_FAILURE;
    }

    if (month[0] == '\0') {
        fputs("Month name cannot be empty.\n", stderr);
        free(month);
        return EXIT_FAILURE;
    }

    puts(month_has_28_days(month) ? "Yes" : "No");

    free(month);
    return EXIT_SUCCESS;
}