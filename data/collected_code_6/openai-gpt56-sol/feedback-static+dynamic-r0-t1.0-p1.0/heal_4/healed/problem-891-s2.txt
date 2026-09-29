#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int digit_count(long long value)
{
    unsigned int count = 1;

    while (value <= -10 || value >= 10) {
        value /= 10;
        ++count;
    }

    return count;
}

static bool have_same_digit_count(long long first, long long second)
{
    return digit_count(first) == digit_count(second);
}

static bool discard_remaining_input(void)
{
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
    }

    return character == '\n';
}

static bool read_number(const char *prompt, long long *value)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end = NULL;
    long long parsed_value;
    int character;

    if (prompt == NULL || value == NULL) {
        return false;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return false;
    }

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 32 : capacity * 2;
            char *new_buffer;

            if (new_capacity <= capacity) {
                free(buffer);
                discard_remaining_input();
                return false;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                discard_remaining_input();
                return false;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (character == EOF && (ferror(stdin) || length == 0)) {
        free(buffer);
        return false;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *new_buffer = realloc(buffer, new_capacity);

        if (new_buffer == NULL) {
            free(buffer);
            return false;
        }

        buffer = new_buffer;
        capacity = new_capacity;
    }

    buffer[length] = '\0';

    errno = 0;
    parsed_value = strtoll(buffer, &end, 10);

    if (errno == ERANGE || end == buffer) {
        free(buffer);
        return false;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return false;
    }

    *value = parsed_value;
    free(buffer);
    return true;
}

int main(void)
{
    long long first;
    long long second;
    const char *message;

    if (!read_number("Enter the first number: ", &first) ||
        !read_number("Enter the second number: ", &second)) {
        if (fputs("Invalid input.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    message = have_same_digit_count(first, second)
                  ? "The numbers have the same number of digits."
                  : "The numbers do not have the same number of digits.";

    if (puts(message) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}