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

static bool read_number(const char *prompt, long long *value)
{
    char buffer[256];
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
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else {
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }
            return false;
        }

        if (ferror(stdin)) {
            return false;
        }
    }

    errno = 0;
    parsed_value = strtoll(buffer, &end, 10);

    if (errno == ERANGE || end == buffer) {
        return false;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
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