#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int average_of_odds(unsigned long long limit, long double *average)
{
    if (average == NULL || limit == 0 || limit % 2 == 0) {
        return -1;
    }

    *average = ((long double)limit + 1.0L) / 2.0L;
    return 0;
}

static int read_line(char *buffer, size_t size)
{
    int ch;

    if (buffer == NULL || size < 2) {
        return -1;
    }

    if (fgets(buffer, size, stdin) == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; ++i) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            return 0;
        }

        if (buffer[i] == '\0') {
            break;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = fgetc(stdin);

    if (ch == '\n' || ch == EOF) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    unsigned long long limit;
    long double average;
    int read_status;

    read_status = read_line(input, sizeof input);

    if (read_status < 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_status > 0) {
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    limit = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid number.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (average_of_odds(limit, &average) != 0) {
        fputs("Enter a positive odd number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Average: %.2Lf\n", average) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}