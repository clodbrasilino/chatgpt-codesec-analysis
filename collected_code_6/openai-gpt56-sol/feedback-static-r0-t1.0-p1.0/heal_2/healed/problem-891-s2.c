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
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n';
}

static bool read_number(const char *prompt, long long *value)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    char *end;
    long long parsed;

    if (prompt == NULL || value == NULL) {
        return false;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return false;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        char *new_buffer;
        size_t new_capacity;

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 32;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(buffer);
                    discard_remaining_input();
                    return false;
                }
                new_capacity = capacity * 2;
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

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(buffer);
        return false;
    }

    if (buffer == NULL) {
        buffer = malloc(1);
        if (buffer == NULL) {
            return false;
        }
    }

    buffer[length] = '\0';

    errno = 0;
    end = NULL;
    parsed = strtoll(buffer, &end, 10);

    if (errno == ERANGE || end == buffer) {
        free(buffer);
        return false;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return false;
    }

    *value = parsed;
    free(buffer);
    return true;
}

int main(void)
{
    long long first;
    long long second;

    if (!read_number("Enter the first number: ", &first) ||
        !read_number("Enter the second number: ", &second)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (have_same_digit_count(first, second)) {
        puts("The numbers have the same number of digits.");
    } else {
        puts("The numbers do not have the same number of digits.");
    }

    return EXIT_SUCCESS;
}