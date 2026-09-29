#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

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
    char *line = NULL;
    char *begin;
    char *end;
    size_t capacity = 0;
    ssize_t length;
    long long parsed_value;

    if (prompt == NULL || value == NULL) {
        return false;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return false;
    }

    errno = 0;
    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return false;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';

        if (length > 0 && line[length - 1] == '\r') {
            line[length - 1] = '\0';
        }
    }

    begin = line;
    while (isspace((unsigned char)*begin)) {
        ++begin;
    }

    errno = 0;
    parsed_value = strtoll(begin, &end, 10);

    if (errno == ERANGE || end == begin) {
        free(line);
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return false;
    }

    *value = parsed_value;
    free(line);
    return true;
}

int main(void)
{
    long long first;
    long long second;
    const char *message;

    if (!read_number("Enter the first number: ", &first) ||
        !read_number("Enter the second number: ", &second)) {
        fputs("Invalid input.\n", stderr);
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