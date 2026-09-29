#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128U

static int average_of_evens(unsigned long long limit, double *average)
{
    if (average == NULL || limit == 0ULL || limit % 2ULL != 0ULL) {
        return -1;
    }

    *average = (double)(limit / 2ULL) + 1.0;
    return 0;
}

static int read_input(char *buffer, size_t size)
{
    size_t length;
    int ch;

    if (buffer == NULL || size < 2U) {
        return -1;
    }

    if (fgets(buffer, size, stdin) == NULL) {
        return -1;
    }

    for (length = 0U;
         length < size && buffer[length] != '\0' && buffer[length] != '\n';
         ++length) {
    }

    if (length < size && buffer[length] == '\n') {
        buffer[length] = '\0';
        return 0;
    }

    ch = fgetc(stdin);

    if (ch == '\n') {
        return 0;
    }

    if (ch == EOF) {
        return ferror(stdin) ? -1 : 0;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    return 1;
}

int main(void)
{
    char input[INPUT_SIZE];
    char *start;
    char *end;
    unsigned long long limit;
    double average;
    int read_status;

    read_status = read_input(input, sizeof input);

    if (read_status < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_status > 0) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;

    while (isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    limit = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (average_of_evens(limit, &average) != 0) {
        fputs("Enter a positive even number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", average) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}