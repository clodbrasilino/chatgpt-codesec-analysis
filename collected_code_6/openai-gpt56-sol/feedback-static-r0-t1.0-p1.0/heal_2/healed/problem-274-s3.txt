#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_index_binomial(unsigned int n, uint64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if (n == 0U) {
        *result = UINT64_C(1);
        return 1;
    }

    if (n > 64U) {
        return 0;
    }

    *result = UINT64_C(1) << (n - 1U);
    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long value;
    uint64_t sum;
    const char *program_name = argc > 0 ? argv[0] : "program";
    const char *input;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer up to 64>\n",
                program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];
    errno = 0;
    value = strtoul(input, &end, 10);

    if (errno != 0 || end == input || *end != '\0' || value > 64UL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!sum_even_index_binomial((unsigned int)value, &sum)) {
        fprintf(stderr, "Unable to compute result\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}