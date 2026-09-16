#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int check_bits_in_range(unsigned int num, int high, int low) {
    if (high < 0 || low < 0 || high >= (int)(sizeof(unsigned int) * CHAR_BIT) || low > high) {
        return 0;
    }

    unsigned int mask;
    if (high == (int)(sizeof(unsigned int) * CHAR_BIT) - 1) {
        mask = ~((1U << low) - 1);
    } else {
        mask = ((1U << (high - low + 1)) - 1) << low;
    }

    if ((num & mask) == num) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)strtoul(argv[1], NULL, 0);
    int high = (int)strtol(argv[2], NULL, 0);
    int low = (int)strtol(argv[3], NULL, 0);

    if (num == 0 && high == 0 && low == 0) {
        return EXIT_SUCCESS;
    }

    int result = check_bits_in_range(num, high, low);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}