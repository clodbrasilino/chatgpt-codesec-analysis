#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int is_divisible(long value, long m, long n)
{
    return value % m == 0 || value % n == 0;
}

static int read_long(const char *text, long *value)
{
    char *end = NULL;
    long result;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    result = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = result;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    long m;
    long n;
    int found = 0;

    if (argc < 4) {
        fprintf(stderr, "Usage: %s m n number [number ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!read_long(argv[1], &m) || !read_long(argv[2], &n)) {
        fprintf(stderr, "Invalid divisor.\n");
        return EXIT_FAILURE;
    }

    if (m == 0 || n == 0) {
        fprintf(stderr, "Divisors must be nonzero.\n");
        return EXIT_FAILURE;
    }

    for (int i = 3; i < argc; ++i) {
        long value;

        if (!read_long(argv[i], &value)) {
            fprintf(stderr, "Invalid number: %s\n", argv[i]);
            return EXIT_FAILURE;
        }

        if (is_divisible(value, m, n)) {
            printf("%s%ld", found ? " " : "", value);
            found = 1;
        }
    }

    if (found) {
        putchar('\n');
    }

    if (ferror(stdout)) {
        fprintf(stderr, "Output error.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}