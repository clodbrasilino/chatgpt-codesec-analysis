#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128U

static unsigned int last_two_digits_of_factorial(unsigned long long n)
{
    unsigned int result = 1U;

    if (n >= 10ULL) {
        return 0U;
    }

    for (unsigned long long i = 2ULL; i <= n; ++i) {
        result = (result * (unsigned int)i) % 100U;
    }

    return result;
}

static int read_input(char *buffer, size_t size)
{
    if (buffer == NULL || size < 2U || size > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    size_t length = 0U;
    while (length < size && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length >= size) {
        return -1;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 0;
    }

    if (feof(stdin)) {
        return 0;
    }

    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    if (ferror(stdin)) {
        return -1;
    }

    return 1;
}

int main(void)
{
    char *input = malloc(INPUT_SIZE);
    if (input == NULL) {
        fputs("Failed to allocate input buffer.\n", stderr);
        return EXIT_FAILURE;
    }

    int read_status = read_input(input, INPUT_SIZE);
    if (read_status < 0) {
        fputs("Failed to read input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (read_status > 0) {
        fputs("Input too long.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    char *start = input;
    while (*start != '\0' && isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        fputs("Invalid input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long n = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        fputs("Invalid input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    unsigned int result = last_two_digits_of_factorial(n);
    free(input);

    if (printf("%02u\n", result) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}