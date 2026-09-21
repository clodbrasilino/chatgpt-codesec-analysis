#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

long long jacobsthal_lucas(int n)
{
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }

    long long prev2 = 2;
    long long prev1 = 1;
    long long current = 0;
    int i;

    for (i = 2; i <= n; i++) {
        if (prev2 > (LLONG_MAX - prev1) / 2) {
            errno = ERANGE;
            return -1;
        }
        current = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_len;
    char *endptr;
    long val;
    int n;
    long long result;

    read_len = getline(&buffer, &buffer_size, stdin);
    if (read_len == -1) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (read_len > 0 && buffer[read_len - 1] == '\n') {
        buffer[read_len - 1] = '\0';
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || val < 0 || val > INT_MAX) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (*endptr != '\0') {
        free(buffer);
        return EXIT_FAILURE;
    }

    n = (int)val;
    errno = 0;
    result = jacobsthal_lucas(n);

    if (errno != 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    free(buffer);
    return EXIT_SUCCESS;
}