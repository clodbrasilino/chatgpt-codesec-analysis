#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 128
#define MAX_DISCARD_CHARS 4096

static long long max2(long long a, long long b)
{
    return (a > b) ? a : b;
}

static long long maxSum(long long n, long long *memo, long long limit)
{
    long long divided;

    if (n <= 0) {
        return 0;
    }

    if (n < limit && memo[n] != -1) {
        return memo[n];
    }

    divided = maxSum(n / 2, memo, limit) +
              maxSum(n / 3, memo, limit) +
              maxSum(n / 4, memo, limit);

    divided = max2(n, divided);

    if (n < limit) {
        memo[n] = divided;
    }

    return divided;
}

static int findMaxSum(long long n, long long *result)
{
    long long *memo;
    long long limit;
    long long i;

    if (n < 0 || result == NULL) {
        return -1;
    }

    if (n >= 999999) {
        limit = 1000000;
    } else {
        limit = n + 1;
    }

    if (limit <= 0) {
        return -1;
    }

    if ((unsigned long long)limit > SIZE_MAX / sizeof(long long)) {
        return -1;
    }

    memo = malloc((size_t)limit * sizeof(long long));
    if (memo == NULL) {
        return -1;
    }

    for (i = 0; i < limit; i++) {
        memo[i] = -1;
    }

    *result = maxSum(n, memo, limit);

    free(memo);
    return 0;
}

static void discardRestOfLine(void)
{
    int c;
    size_t count = 0;

    do {
        c = getchar();
        count++;
    } while (c != '\n' && c != EOF && count < MAX_DISCARD_CHARS);
}

static int readNonNegative(long long *out)
{
    char buffer[INPUT_BUFFER_SIZE];
    char *endptr;
    long long value;

    if (out == NULL) {
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        return -1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        discardRestOfLine();
        return -1;
    }

    errno = 0;
    endptr = NULL;
    value = strtoll(buffer, &endptr, 10);

    if (endptr == buffer) {
        return -1;
    }

    if (errno == ERANGE) {
        return -1;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            return -1;
        }
        endptr++;
    }

    if (value < 0) {
        return -1;
    }

    *out = value;
    return 0;
}

int main(void)
{
    long long n;
    long long result;

    printf("Enter a non-negative number: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (readNonNegative(&n) != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (findMaxSum(n, &result) != 0) {
        fprintf(stderr, "Computation failed\n");
        return EXIT_FAILURE;
    }

    printf("Maximum sum for %lld is %lld\n", n, result);

    return EXIT_SUCCESS;
}