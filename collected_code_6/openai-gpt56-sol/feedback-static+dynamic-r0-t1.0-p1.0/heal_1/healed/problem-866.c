#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int equals_ignore_case(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return 0;
    }

    while (*first != '\0' && *second != '\0') {
        if (tolower((unsigned char)*first) !=
            tolower((unsigned char)*second)) {
            return 0;
        }

        ++first;
        ++second;
    }

    return *first == '\0' && *second == '\0';
}

static int month_has_31_days(const char *month)
{
    static const char *const months[] = {
        "January",
        "March",
        "May",
        "July",
        "August",
        "October",
        "December"
    };
    size_t i;

    if (month == NULL) {
        return 0;
    }

    for (i = 0; i < sizeof months / sizeof months[0]; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

static char *read_line(FILE *stream)
{
    char *line = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    while ((character = fgetc(stream)) != EOF && character != '\n') {
        char *resized;
        size_t new_capacity;

        if (character == '\r') {
            int next = fgetc(stream);

            if (next != '\n' && next != EOF) {
                ungetc(next, stream);
            }
            break;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 16;
            } else {
                if (capacity > (size_t)-1 / 2) {
                    free(line);
                    return NULL;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return NULL;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (character == EOF && length == 0) {
        free(line);
        return NULL;
    }

    if (line == NULL) {
        line = malloc(1);
        if (line == NULL) {
            return NULL;
        }
    }

    line[length] = '\0';
    return line;
}

int main(void)
{
    char *month = read_line(stdin);

    if (month == NULL) {
        fprintf(stderr, "Failed to read the month name.\n");
        return EXIT_FAILURE;
    }

    if (month[0] == '\0') {
        fprintf(stderr, "Month name cannot be empty.\n");
        free(month);
        return EXIT_FAILURE;
    }

    puts(month_has_31_days(month) ? "Yes" : "No");

    free(month);
    return EXIT_SUCCESS;
}