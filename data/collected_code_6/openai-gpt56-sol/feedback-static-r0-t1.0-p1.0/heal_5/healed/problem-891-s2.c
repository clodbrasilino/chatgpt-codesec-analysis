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
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    long long parsed;

    if (prompt == NULL || value == NULL) {
        return false;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return false;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return false;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    errno = 0;
    parsed = strtoll(line, &end, 10);

    if (errno == ERANGE || end == line) {
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

    *value = parsed;
    free(line);
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