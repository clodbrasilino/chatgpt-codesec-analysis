#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t toggle_odd_bits(uint32_t num)
{
    return num ^ UINT32_C(0xAAAAAAAA);
}

int main(void)
{
    uint32_t num;
    char buffer[64];
    char extra;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    if (sscanf(buffer, "%" SCNu32 " %c", &num, &extra) != 1) {
        return 1;
    }

    printf("%" PRIu32 "\n", toggle_odd_bits(num));

    return 0;
}