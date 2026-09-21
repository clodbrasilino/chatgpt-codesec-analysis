#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int square_perimeter(long long side, long long *perimeter)
{
    if (perimeter == NULL || side < 0 || side > LLONG_MAX / 4) {
        return 0;
    }

    *perimeter = side * 4;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end = NULL;
    long long side;
    long long perimeter;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtoll(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || !square_perimeter(side, &perimeter)) {
        return EXIT_FAILURE;
    }

    if (printf("%lld\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}