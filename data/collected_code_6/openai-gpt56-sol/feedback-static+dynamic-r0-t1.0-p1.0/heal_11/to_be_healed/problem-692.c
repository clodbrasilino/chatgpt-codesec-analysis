#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128U

static unsigned int last_two_digits_of_factorial(unsigned long long n)
{
    unsigned int result = 1U;

    if (n >= 10ULL) {
        return 0U;
    }

    for (unsigned int i = 2U; i <= (unsigned int)n; ++i) {
        result = (result * i) % 100U;
    }

    return result;
}

static int read_input(char *buffer, size_t size)
{
    if (buffer == NULL || size < 2U) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return ferror(stdin) ? -1 : 0;
    }

    size_t length = 0U;

    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int ch = fgetc(stdin);

    if (ch == EOF) {
        return ferror(stdin) ? -1 : 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    buffer[0] = '\0';

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    return 1;
}

int main(void)
{
    char *input = malloc(INPUT_SIZE);

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
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

    while (*start != '\0' && isspace((unsigned char)*start)) {
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

    while (*end != '\0' && isspace((unsigned char)*end)) {
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