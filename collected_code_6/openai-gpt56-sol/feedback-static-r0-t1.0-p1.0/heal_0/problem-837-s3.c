#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum_first_n_odds(uint64_t n, uint64_t *result)
{
    uint64_t n_squared;

    if (result == NULL) {
        return 0;
    }

    if (n != 0 && n > UINT64_MAX / n) {
        return 0;
    }

    n_squared = n * n;

    if (n_squared != 0 && n_squared > UINT64_MAX / n_squared) {
        return 0;
    }

    *result = n_squared * n_squared;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-' || argv[1][0] == '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    input = strtoumax(argv[1], &end, 10);

    if (*end != '\0' || input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!cube_sum_first_n_odds((uint64_t)input, &result)) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}