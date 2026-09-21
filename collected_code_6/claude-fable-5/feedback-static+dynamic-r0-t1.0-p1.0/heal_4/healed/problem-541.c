#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define BUFFER_SIZE 64

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

static int read_line(char *buffer, size_t size)
{
    char *newline;
    int ch;

    if (buffer == NULL || size < 2) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1] = '\0';

    newline = memchr(buffer, '\n', size);
    if (newline != NULL) {
        *newline = '\0';
        return 0;
    }

    ch = getchar();
    if (ch == '\n' || ch == EOF) {
        return 0;
    }

    while (ch != '\n' && ch != EOF) {
        ch = getchar();
    }

    return 1;
}

static int parse_positive_ulong(const char *buffer, unsigned long *out)
{
    const char *p;
    char *endptr;
    unsigned long value;

    if (buffer == NULL || out == NULL) {
        return -1;
    }

    p = buffer;
    while (*p != '\0' && isspace((unsigned char)*p)) {
        p++;
    }

    if (*p == '+') {
        p++;
    }

    if (!isdigit((unsigned char)*p)) {
        return -1;
    }

    errno = 0;
    endptr = NULL;
    value = strtoul(p, &endptr, 10);

    if (endptr == p || errno == ERANGE) {
        return -1;
    }

    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            return -1;
        }
        endptr++;
    }

    if (value == 0UL) {
        return -1;
    }

    *out = value;
    return 0;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    unsigned long number;
    int status;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a positive integer: ");
    fflush(stdout);

    status = read_line(buffer, sizeof(buffer));
    if (status < 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    if (status > 0) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    if (parse_positive_ulong(buffer, &number) != 0) {
        fprintf(stderr, "Invalid input: expected a positive integer\n");
        return EXIT_FAILURE;
    }

    if (is_abundant(number)) {
        printf("%lu is an abundant number\n", number);
    } else {
        printf("%lu is not an abundant number\n", number);
    }

    return EXIT_SUCCESS;
}