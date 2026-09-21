#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

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

static bool read_line(char *buf, size_t size)
{
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (buf == NULL || size == 0U) {
        return false;
    }

    if (fgets(buf, (int)size, stdin) == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buf);
    if (len > 0U && buf[len - 1U] == '\n') {
        buf[len - 1U] = '\0';
    } else {
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
        return false;
    }

    return true;
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
    char buffer[64];
    unsigned long value;

    printf("Enter a positive integer: ");
    fflush(stdout);

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