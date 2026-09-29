#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t toggle_even_bits(uint32_t value)
{
    return value ^ UINT32_C(0x55555555);
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    uint32_t value;
    char extra;

    if (getline(&input, &capacity, stdin) < 0) {
        fputs("Invalid input\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (sscanf(input, "%" SCNu32 " %c", &value, &extra) != 1) {
        fputs("Invalid input\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIu32 "\n", toggle_even_bits(value)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}