#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int is_palindrome(unsigned long long n)
{
    char buf[32];
    int len;
    int i;
    int j;

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
    char line[64];
    char *endptr;
    unsigned long long n;
    unsigned long long result;
    size_t i;

    printf("Enter a non-negative number: ");
    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (fgets(line, sizeof line, stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    if (strchr(line, '\n') == NULL && !feof(stdin)) {
        fprintf(stderr, "Error: input too long\n");
        return EXIT_FAILURE;
    }

    i = 0;
    while (line[i] != '\0' && isspace((unsigned char)line[i])) {
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
    if (endptr == &line[i]) {
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