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

    do {
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);

    return character == '\n';
}

static bool read_number(const char *prompt, long long *value)
{
    char buffer[128];
    char *end;
    long long parsed_value;

    if (prompt == NULL || value == NULL) {
        return false;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return false;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return false;
    }

    char *newline = NULL;

    for (size_t i = 0; i < sizeof buffer; ++i) {
        if (buffer[i] == '\n') {
            newline = &buffer[i];
            break;
        }

        if (buffer[i] == '\0') {
            break;
        }
    }

    if (newline == NULL) {
        if (!feof(stdin)) {
            (void)discard_remaining_input();
        }
        return false;
    }

    errno = 0;
    parsed_value = strtoll(buffer, &end, 10);

    if (errno == ERANGE || end == buffer) {
        return false;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    *value = parsed_value;
    return true;
}

int main(void)
{
    long long first;
    long long second;

    if (!read_number("Enter the first number: ", &first) ||
        !read_number("Enter the second number: ", &second)) {
        (void)fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    const char *message = have_same_digit_count(first, second)
                              ? "The numbers have the same number of digits."
                              : "The numbers do not have the same number of digits.";

    if (puts(message) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}