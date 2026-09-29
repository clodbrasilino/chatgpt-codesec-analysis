#include <stdio.h>
#include <stdlib.h>

unsigned int count_set_bits_up_to_n(unsigned int n) {
    unsigned int total = 0;
    unsigned int i = 0;
    unsigned int power_of_2 = 1;

    while (power_of_2 <= n) {
        unsigned int pairs = (n + 1) / (power_of_2 << 1);
        total += pairs * power_of_2;
        
        unsigned int remainder = (n + 1) % (power_of_2 << 1);
        if (remainder > power_of_2) {
            total += remainder - power_of_2;
        }
        
        power_of_2 <<= 1;
        i++;
    }
    
    return total;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > __UINT32_MAX__) {
        fprintf(stderr, "Invalid input: Not a valid positive integer within 32-bit range.\n");
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    unsigned int result = count_set_bits_up_to_n(n);
    printf("%u\n", result);

    return EXIT_SUCCESS;
}