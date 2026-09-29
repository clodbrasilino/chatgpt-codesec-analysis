#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int equals_ignore_case(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return 0;
    }

    while (*first != '\0' && *second != '\0') {
        unsigned char first_char = (unsigned char)*first;
        unsigned char second_char = (unsigned char)*second;

        if (tolower(first_char) != tolower(second_char)) {
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

    for (i = 0; i < sizeof(months) / sizeof(months[0]); ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

static int read_month(char **month)
{
    enum { MAX_MONTH_LENGTH = 9 };
    char buffer[MAX_MONTH_LENGTH + 2];
    size_t length;
    int character;

    if (month == NULL) {
        return 0;
    }

    *month = NULL;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n' &&
           buffer[length] != '\r') {
        ++length;
    }

    if (buffer[length] == '\0') {
        character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }
            return 0;
        }
    }

    if (length == 0) {
        return 0;
    }

    buffer[length] = '\0';

    *month = malloc(length + 1);
    if (*month == NULL) {
        return -1;
    }

    for (size_t i = 0; i <= length; ++i) {
        (*month)[i] = buffer[i];
    }

    return 1;
}

int main(void)
{
    char *month = NULL;
    int status = read_month(&month);

    if (status < 0) {
        fputs("Failed to allocate memory for the month name.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        if (ferror(stdin)) {
            fputs("Failed to read the month name.\n", stderr);
        } else {
            fputs("Month name is empty, invalid, or too long.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    puts(month_has_31_days(month) ? "Yes" : "No");
    free(month);

    return EXIT_SUCCESS;
}