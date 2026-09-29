#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

#define NUM_BUF_SIZE 32
#define LINE_BUF_SIZE 64

static int is_palindrome(unsigned long long n)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[NUM_BUF_SIZE];
    int len;
    int i;
    int j;

    memset(buf, 0, sizeof buf);

    len = snprintf(buf, sizeof buf, "%llu", n);
    if (len < 0 || (size_t)len >= sizeof buf) {
        return 0;
    }

    i = 0;
    j = len - 1;
    while (i < j) {
        if (buf[i] != buf[j]) {
            return 0;
        }
        i++;
        j--;
    }
    return 1;
}

static int next_smallest_palindrome(unsigned long long n, unsigned long long *result)
{
    if (result == NULL) {
        return -1;
    }
    while (n < ULLONG_MAX) {
        n++;
        if (is_palindrome(n)) {
            *result = n;
            return 0;
        }
    }
    return -1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char line[LINE_BUF_SIZE];
    char *endptr;
    unsigned long long n;
    unsigned long long result;
    size_t i;

    memset(line, 0, sizeof line);

    printf("Enter a non-negative number: ");
    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (fgets(line, sizeof line, stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }
    line[sizeof line - 1] = '\0';

    if (strchr(line, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "Error: input too long\n");
        return EXIT_FAILURE;
    }

    i = 0;
    while (i < sizeof line - 1 && line[i] != '\0' && isspace((unsigned char)line[i])) {
        i++;
    }
    if (line[i] == '-' || line[i] == '+' || !isdigit((unsigned char)line[i])) {
        fprintf(stderr, "Error: input must be a non-negative integer\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    endptr = NULL;
    n = strtoull(&line[i], &endptr, 10);
    if (errno == ERANGE) {
        fprintf(stderr, "Error: number out of range\n");
        return EXIT_FAILURE;
    }
    if (endptr == NULL || endptr == &line[i]) {
        fprintf(stderr, "Error: no digits found\n");
        return EXIT_FAILURE;
    }
    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            fprintf(stderr, "Error: trailing characters in input\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }

    if (next_smallest_palindrome(n, &result) != 0) {
        fprintf(stderr, "Error: no palindrome found within range\n");
        return EXIT_FAILURE;
    }

    printf("Next smallest palindrome: %llu\n", result);
    return EXIT_SUCCESS;
}