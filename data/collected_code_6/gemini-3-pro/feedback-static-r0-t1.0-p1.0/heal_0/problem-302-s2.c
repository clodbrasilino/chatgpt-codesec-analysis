#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int findMostSignificantSetBit(uint32_t n) {
    if (n == 0) {
        return -1;
    }
    
    int position = 0;
    while (n > 1) {
        n >>= 1;
        position++;
    }
    
    return position;
}

int main(void) {
    uint32_t num = 0;
    int msb_pos = 0;

    if (scanf("%u", &num) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    msb_pos = findMostSignificantSetBit(num);

    if (msb_pos == -1) {
        printf("No set bits found (number is 0).\n");
    } else {
        printf("%d\n", msb_pos);
    }

    return EXIT_SUCCESS;
}