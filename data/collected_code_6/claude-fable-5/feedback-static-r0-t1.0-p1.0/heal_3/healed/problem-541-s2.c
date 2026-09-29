#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define BUFFER_SIZE 64

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

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    char *endptr;
    const char *start;
    const char *newline;
    unsigned long value;
    size_t len;

    printf("Enter a positive integer: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    newline = memchr(buffer, '\n', sizeof(buffer));
    if (newline != NULL) {
        len = (size_t)(newline - buffer);
    } else {
        len = strnlen(buffer, sizeof(buffer) - 1);
        if (len == sizeof(buffer) - 1 && !feof(stdin)) {
            fprintf(stderr, "Input too long\n");
            flush_stdin();
            return EXIT_FAILURE;
        }
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    start = buffer;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        start++;
    }

    if (*start == '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (*start == '-' || *start == '+') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!isdigit((unsigned char)*start)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    endptr = NULL;
    value = strtoul(start, &endptr, 10);

    if (endptr == start) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE) {
        fprintf(stderr, "Value out of range\n");
        return EXIT_FAILURE;
    }

    while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
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