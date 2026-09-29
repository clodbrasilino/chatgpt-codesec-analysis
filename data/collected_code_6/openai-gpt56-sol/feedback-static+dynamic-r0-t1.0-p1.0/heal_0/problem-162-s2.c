#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_positive_sequence(int64_t n, int64_t *result)
{
    if (result == NULL || n <= 0) {
        return -1;
    }

    int64_t terms = (n + 1) / 2;
    *result = terms * (n - terms + 1);
    return 0;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    int64_t n;
    int64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoimax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || sum_positive_sequence(n, &sum) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}