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

    while ((character = getchar()) != '\n' && character != EOF) {
    }

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

    size_t length = 0;
    while (length < sizeof buffer && buffer[length] != '\0') {
        ++length;
    }

    if (length == sizeof buffer) {
        return false;
    }

    if (length == 0 || buffer[length - 1] != '\n') {
        if (!feof(stdin)) {
            discard_remaining_input();
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
        if (fputs("Invalid input.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (have_same_digit_count(first, second)) {
        if (puts("The numbers have the same number of digits.") == EOF) {
            return EXIT_FAILURE;
        }
    } else {
        if (puts("The numbers do not have the same number of digits.") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}