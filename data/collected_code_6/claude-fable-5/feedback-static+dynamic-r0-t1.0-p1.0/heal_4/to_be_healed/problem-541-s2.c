#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define INPUT_BUFFER_SIZE 64U

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

static void discard_remaining_input(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

static bool read_line(char *buf, size_t size)
{
    size_t len;

    if (buf == NULL || size < 2U) {
        return false;
    }

    if (fgets(buf, (int)size, stdin) == NULL) {
        return false;
    }

    buf[size - 1U] = '\0';
    len = strnlen(buf, size);

    if (len > 0U && buf[len - 1U] == '\n') {
        buf[len - 1U] = '\0';
        return true;
    }

    discard_remaining_input();
    return false;
}

static bool parse_ulong(const char *buf, unsigned long *out)
{
    char *endptr;
    unsigned long value;
    const char *p;

    if (buf == NULL || out == NULL) {
        return false;
    }

    p = buf;
    while (isspace((unsigned char)*p)) {
        p++;
    }

    if (*p == '\0' || *p == '-') {
        return false;
    }

    errno = 0;
    endptr = NULL;
    value = strtoul(p, &endptr, 10);

    if (endptr == p) {
        return false;
    }

    if (errno == ERANGE) {
        return false;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        return false;
    }

    *out = value;
    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[INPUT_BUFFER_SIZE];
    unsigned long value;

    printf("Enter a positive integer: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    memset(buffer, 0, sizeof(buffer));

    if (!read_line(buffer, sizeof(buffer))) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (!parse_ulong(buffer, &value)) {
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