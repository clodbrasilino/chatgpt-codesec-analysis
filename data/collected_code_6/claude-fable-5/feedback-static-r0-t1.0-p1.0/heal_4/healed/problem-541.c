#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

#define BUFFER_SIZE 64
#define FLUSH_GUARD_LIMIT 1000000UL

static int is_abundant(unsigned long n)
{
    unsigned long sum;
    unsigned long i;

    if (n < 12UL) {
        return 0;
    }

    sum = 1UL;
    for (i = 2UL; i <= n / i; i++) {
        if (n % i == 0UL) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
            if (sum > n) {
                return 1;
            }
        }
    }

    return (sum > n) ? 1 : 0;
}

static int flush_stdin_line(void)
{
    int ch;
    int truncated = 0;
    unsigned long guard = 0UL;

    do {
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            truncated = 1;
        }
        guard++;
        if (guard >= FLUSH_GUARD_LIMIT) {
            truncated = 1;
            break;
        }
    } while (ch != '\n' && ch != EOF);

    return truncated;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    char *endptr;
    char *newline;
    unsigned long number;
    const char *p;

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
        *newline = '\0';
    } else {
        if (flush_stdin_line()) {
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    }

    p = buffer;
    while (*p != '\0' && isspace((unsigned char)*p)) {
        p++;
    }

    if (*p == '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (*p == '-' || *p == '+') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!isdigit((unsigned char)*p)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoul(p, &endptr, 10);

    if (endptr == p || errno != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (number == 0UL) {
        fprintf(stderr, "Number must be positive\n");
        return EXIT_FAILURE;
    }

    if (is_abundant(number)) {
        printf("%lu is an abundant number\n", number);
    } else {
        printf("%lu is not an abundant number\n", number);
    }

    return EXIT_SUCCESS;
}