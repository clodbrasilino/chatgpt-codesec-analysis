#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>

#define INPUT_BUFFER_SIZE 64

static int count_primes(unsigned long n, unsigned long *result)
{
    unsigned char *sieve;
    unsigned long i;
    unsigned long j;
    unsigned long count;

    if (result == NULL) {
        return -1;
    }

    if (n < 3UL) {
        *result = 0UL;
        return 0;
    }

    if (n > (unsigned long)SIZE_MAX) {
        return -1;
    }

    sieve = malloc((size_t)n);
    if (sieve == NULL) {
        return -1;
    }

    memset(sieve, 1, (size_t)n);
    sieve[0] = 0;
    sieve[1] = 0;

    for (i = 2UL; i <= (n - 1UL) / i; i++) {
        if (sieve[i] == 1) {
            for (j = i * i; j < n; j += i) {
                sieve[j] = 0;
            }
        }
    }

    count = 0UL;
    for (i = 2UL; i < n; i++) {
        if (sieve[i] == 1) {
            count++;
        }
    }

    free(sieve);
    *result = count;
    return 0;
}

static int read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size < 2 || size > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1] = '\0';

    len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == size - 1) {
        return -1;
    }

    return 0;
}

static int parse_unsigned_long(const char *input, unsigned long *value)
{
    const char *p;
    char *endptr;
    unsigned long n;

    if (input == NULL || value == NULL) {
        return -1;
    }

    p = input;
    while (isspace((unsigned char)*p)) {
        p++;
    }

    if (*p == '-' || *p == '\0') {
        return -1;
    }

    errno = 0;
    n = strtoul(p, &endptr, 10);
    if (endptr == p || errno != 0) {
        return -1;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    if (*endptr != '\0') {
        return -1;
    }

    *value = n;
    return 0;
}

int main(void)
{
    unsigned long n;
    unsigned long result;
    char buffer[INPUT_BUFFER_SIZE];

    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (parse_unsigned_long(buffer, &n) != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (count_primes(n, &result) != 0) {
        fprintf(stderr, "Failed to count primes\n");
        return EXIT_FAILURE;
    }

    printf("%lu\n", result);
    return EXIT_SUCCESS;
}