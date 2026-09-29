#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int equals_ignore_case(const char *left, const char *right)
{
    if (left == NULL || right == NULL) {
        return 0;
    }

    while (*left != '\0' && *right != '\0') {
        unsigned char left_char = (unsigned char)*left;
        unsigned char right_char = (unsigned char)*right;

        if (tolower(left_char) != tolower(right_char)) {
            return 0;
        }

        ++left;
        ++right;
    }

    return *left == '\0' && *right == '\0';
}

static int month_has_30_days(const char *month)
{
    static const char *const months[] = {
        "April",
        "June",
        "September",
        "November"
    };

    size_t count = sizeof(months) / sizeof(months[0]);

    for (size_t i = 0; i < count; ++i) {
        if (equals_ignore_case(month, months[i])) {
            return 1;
        }
    }

    return 0;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    while ((character = fgetc(stream)) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 32 : capacity * 2;

            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }

            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (character == EOF && ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (character == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    if (length + 1 > capacity) {
        char *new_buffer = realloc(buffer, length + 1);

        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *month = read_line(stdin);

    if (month == NULL) {
        fputs("Failed to read the month.\n", stderr);
        return 1;
    }

    if (month[0] == '\0') {
        fputs("Month name cannot be empty.\n", stderr);
        free(month);
        return 1;
    }

    puts(month_has_30_days(month) ? "Yes" : "No");

    free(month);
    return 0;
}