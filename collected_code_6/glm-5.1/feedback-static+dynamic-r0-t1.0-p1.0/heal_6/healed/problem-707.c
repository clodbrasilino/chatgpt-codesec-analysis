#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

unsigned int count_set_bits_up_to_n(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    unsigned int msb_pos = 0;
    unsigned int temp = n;
    while (temp >>= 1) {
        msb_pos++;
    }
    unsigned int msb = 1U << msb_pos;
    unsigned int count = msb_pos * (msb >> 1);
    count += (n - msb + 1);
    count += count_set_bits_up_to_n(n - msb);
    printf("%u\n", count);
    return count;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > UINT32_MAX) {
        return EXIT_FAILURE;
    }
    unsigned int n = (unsigned int)val;
    count_set_bits_up_to_n(n);
    return EXIT_SUCCESS;
}