#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128

static bool is_prime(int value)
{
    if (value < 2) {
        return false;
    }

    if (value == 2) {
        return true;
    }

    if (value % 2 == 0) {
        return false;
    }

    for (int divisor = 3; divisor <= value / divisor; divisor += 2) {
        if (value % divisor == 0) {
            return false;
        }
    }

    return true;
}

static bool discard_line(void)
{
    char buffer[INPUT_SIZE];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        size_t i = 0;

        while (buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                return true;
            }
            ++i;
        }
    }

    return feof(stdin) != 0;
}

static bool read_line(char *buffer, size_t size)
{
    if (buffer == NULL || size < 2 || size > INT_MAX) {
        return false;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }

    size_t length = 0;

    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return true;
    }

    if (feof(stdin)) {
        return true;
    }

    discard_line();
    return false;
}

int main(void)
{
    char input[INPUT_SIZE];

    if (!read_line(input, sizeof input)) {
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    long value = strtol(input, &end, 10);

    if (errno == ERANGE || end == input ||
        value < INT_MIN || value > INT_MAX) {
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", is_prime((int)value) ? "prime" : "not prime") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}