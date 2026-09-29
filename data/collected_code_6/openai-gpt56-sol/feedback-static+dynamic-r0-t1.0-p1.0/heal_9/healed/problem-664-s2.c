#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int average_of_evens(unsigned long long limit, double *average)
{
    if (average == NULL || limit == 0ULL || limit % 2ULL != 0ULL) {
        return -1;
    }

    *average = (double)(limit / 2ULL) + 1.0;
    return 0;
}

static int read_input(char **buffer)
{
    enum { INPUT_CAPACITY = 256 };
    char input[INPUT_CAPACITY];
    size_t length;
    char *copy;
    int ch;

    if (buffer == NULL) {
        return -1;
    }

    *buffer = NULL;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return feof(stdin) ? 1 : -1;
    }

    length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin)) {
            return -1;
        }

        return 2;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return -1;
    }

    memcpy(copy, input, length + 1U);
    *buffer = copy;

    return 0;
}

int main(void)
{
    char *input = NULL;
    char *start;
    char *end;
    unsigned long long limit;
    double average;
    int status;

    status = read_input(&input);

    if (status < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        fputs("Invalid input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    limit = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        fputs("Invalid number.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

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