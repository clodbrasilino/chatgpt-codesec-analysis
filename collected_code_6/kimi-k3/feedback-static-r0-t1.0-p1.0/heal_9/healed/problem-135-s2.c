#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

static bool hexagonal_number(uint64_t n, uint64_t *result)
{
    if (n == 0) {
        return false;
    }
    if (n > UINT64_MAX / (2 * n - 1)) {
        return false;
    }
    *result = n * (2 * n - 1);
    return true;
}

int main(void)
{
    uint64_t n;
    uint64_t result;
    char buffer[128];
    char *endptr;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    n = strtoull(buffer, &endptr, 10);

    if (errno == ERANGE || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (!hexagonal_number(n, &result)) {
        fprintf(stderr, "Overflow or invalid input\n");
        return 1;
    }

    printf("%" PRIu64 "\n", result);
    return 0;
}