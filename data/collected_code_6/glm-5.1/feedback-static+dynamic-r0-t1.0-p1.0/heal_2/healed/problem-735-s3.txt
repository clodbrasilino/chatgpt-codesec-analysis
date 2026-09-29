#include <stdio.h>
#include <stdlib.h>

unsigned int toggle_middle_bits(unsigned int num) {
    if (num <= 1) {
        return num;
    }
    int bits = sizeof(unsigned int) * 8;
    int msb_pos = bits - 1;
    while (msb_pos > 0 && !((num >> msb_pos) & 1)) {
        msb_pos--;
    }
    unsigned int mask = (~0U >> (bits - msb_pos)) << 1;
    return num ^ mask;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return 1;
    }
    char *endptr;
    unsigned int num = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        return 1;
    }
    unsigned int result = toggle_middle_bits(num);
    printf("%u\n", result);
    return 0;
}