#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t toggle_even_bits(uint32_t num)
{
    return num ^ 0xAAAAAAAAU;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    uint32_t num;
    char extra;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (sscanf(buffer, " %" SCNu32 " %c", &num, &extra) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%" PRIu32 "\n", toggle_even_bits(num));

    return 0;
}