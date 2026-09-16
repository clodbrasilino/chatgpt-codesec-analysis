#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool has_even_parity(unsigned int num);

bool has_even_parity(unsigned int num) {
    unsigned int parity = 0;
    while (num > 0) {
        parity ^= (num & 1);
        num >>= 1;
    }
    return parity == 0;
}

int main(void) {
    unsigned int number = 0;
    int result = 0;

    result = scanf("%u", &number);

    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (has_even_parity(number)) {
        printf("Even parity\n");
    } else {
        printf("Odd parity\n");
    }

    return EXIT_SUCCESS;
}