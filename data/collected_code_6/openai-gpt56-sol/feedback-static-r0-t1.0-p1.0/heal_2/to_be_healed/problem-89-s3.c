#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int closest_smaller(int n, int *result)
{
    if (result == NULL || n == INT_MIN) {
        return 0;
    }

    *result = n - 1;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end = NULL;
    long value;
    int result;

    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        value < INT_MIN || value > INT_MAX) {
        (void)fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    if (!closest_smaller((int)value, &result)) {
        (void)fprintf(stderr, "No smaller int value exists\n");
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}