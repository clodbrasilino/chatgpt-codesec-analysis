#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

#define BUFFER_SIZE 64
#define MAX_FLUSH_ITERATIONS 4096

static bool is_abundant(unsigned long n)
{
    unsigned long sum;
    unsigned long i;

    if (n < 2UL) {
        return false;
    }

    sum = 1UL;
    for (i = 2UL; i <= n / i; i++) {
        if (n % i == 0UL) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }

    return sum > n;
}

static void flush_stdin(void)
{
    int ch;
    size_t count;

    count = 0;
    do {
        ch = fgetc(stdin);
        count++;
    } while (ch != '\n' && ch != EOF && count < MAX_FLUSH_ITERATIONS);
}

static bool read_line(char *buffer, size_t size, size_t *out_len)
{
    const char *newline;
    size_t len;

    if (buffer == NULL || size == 0 || size > (size_t)INT_MAX || out_len == NULL) {
        return false;
    }

    memset(buffer, 0, size);

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }

    buffer[size - 1] = '\0';

    newline = memchr(buffer, '\n', size);
    if (newline != NULL) {
        len = (size_t)(newline - buffer);
    } else {
        len = strnlen(buffer, size - 1);
        if (len == size - 1 && !feof(stdin)) {
            flush_stdin();
            return false;
        }
    }

    *out_len = len;
    return true;
}

static bool parse_unsigned_long(const char *input, unsigned long *out_value)
{
    const char *start;
    char *endptr;
    unsigned long value;

    if (input == NULL || out_value == NULL) {
        return false;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        start++;
    }

    if (*start == '\0') {
        return false;
    }

    if (*start == '-' || *start == '+') {
        return false;
    }

    if (!isdigit((unsigned char)*start)) {
        return false;
    }

    errno = 0;
    endptr = NULL;
    value = strtoul(start, &endptr, 10);

    if (endptr == start) {
        return false;
    }

    if (errno == ERANGE) {
        return false;
    }

    while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        return false;
    }

    *out_value = value;
    return true;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    unsigned long value;
    size_t len;

    printf("Enter a positive integer: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    len = 0;
    if (!read_line(buffer, sizeof(buffer), &len)) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    value = 0UL;
    if (!parse_unsigned_long(buffer, &value)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_abundant(value)) {
        printf("%lu is an abundant number\n", value);
    } else {
        printf("%lu is not an abundant number\n", value);
    }

    return EXIT_SUCCESS;
}