#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int carol_number(unsigned int n, uint64_t *result)
{
    uint64_t power = 2;

    if (result == NULL || n == 0U) {
        return 0;
    }

    for (unsigned int i = 1U; i < n; ++i) {
        if (power > UINT64_MAX / 2U) {
            return 0;
        }
        power *= 2U;
    }

    if (power > (UINT64_MAX - 2U) / power) {
        return 0;
    }

    *result = power * power - 2U * power - 1U;
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive-index>\n", argv[0]);
        return EXIT_FAILURE;
    }

    input = strtoul(argv[1], &end, 10);

    if (argv[1][0] == '\0' || end == NULL || *end != '\0' ||
        input == 0UL || input > UINT32_MAX) {
        fprintf(stderr, "Invalid index\n");
        return EXIT_FAILURE;
    }

    if (!carol_number((unsigned int)input, &result)) {
        fprintf(stderr, "Carol number exceeds the supported range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}