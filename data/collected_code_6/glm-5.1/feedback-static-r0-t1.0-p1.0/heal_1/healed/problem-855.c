#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int check_even_parity(unsigned int num) {
    int count = 0;
    while (num) {
        count ^= (num & 1);
        num >>= 1;
    }
    return count == 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > UINT32_MAX) {
        return EXIT_FAILURE;
    }

    if (check_even_parity((unsigned int)val)) {
        printf("Even Parity\n");
    } else {
        printf("Odd Parity\n");
    }

    return EXIT_SUCCESS;
}