#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

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

    if (*str == '-' || *str == '\0') {
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

static int read_line(char *buf, size_t size)
{
    size_t len = 0;

    if (buf == NULL || size == 0) {
        return -1;
    }

    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }

    len = strcspn(buf, "\n");

    if (buf[len] == '\0' && len == size - 1) {
        int ch = 0;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
            ;
        }
        return -1;
    }

    buf[len] = '\0';
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    unsigned long long number = 0ULL;
    int result = 0;

    printf("Enter a non-negative integer: ");
    fflush(stdout);

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