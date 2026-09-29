#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 64
#define MAX_DISCARD_ITERATIONS 4096

static int digit_sum(unsigned long long n)
{
    int sum = 0;

    while (n > 0ULL) {
        sum += (int)(n % 10ULL);
        n /= 10ULL;
    }

    return sum;
}

static int parse_non_negative(const char *str, unsigned long long *out)
{
    char *endptr = NULL;
    unsigned long long value = 0ULL;

    if (str == NULL || out == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '-' || *str == '+' || *str == '\0') {
        return -1;
    }

    if (!isdigit((unsigned char)*str)) {
        return -1;
    }

    errno = 0;
    value = strtoull(str, &endptr, 10);

    if (errno == ERANGE) {
        return -1;
    }

    if (endptr == str) {
        return -1;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        return -1;
    }

    *out = value;
    return 0;
}

static void discard_remaining_input(void)
{
    int ch = 0;
    size_t iterations = 0;

    do {
        ch = getchar();
        iterations++;
    } while (ch != '\n' && ch != EOF && iterations < MAX_DISCARD_ITERATIONS);
}

static int read_line(char *buf, size_t size)
{
    size_t len = 0;

    if (buf == NULL || size < 2 || size > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }

    buf[size - 1] = '\0';
    len = strcspn(buf, "\n");

    if (buf[len] == '\0' && len == size - 1) {
        discard_remaining_input();
        return -1;
    }

    buf[len] = '\0';
    return 0;
}

int main(void)
{
    char buffer[INPUT_BUFFER_SIZE];
    unsigned long long number = 0ULL;
    int result = 0;

    memset(buffer, 0, sizeof(buffer));

    if (printf("Enter a non-negative integer: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (parse_non_negative(buffer, &number) != 0) {
        fprintf(stderr, "Error: invalid non-negative integer input.\n");
        return EXIT_FAILURE;
    }

    result = digit_sum(number);

    if (printf("Digit sum of %llu is %d\n", number, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}