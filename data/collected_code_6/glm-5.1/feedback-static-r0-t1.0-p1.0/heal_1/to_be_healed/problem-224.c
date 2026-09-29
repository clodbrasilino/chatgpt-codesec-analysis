#include <stdio.h>
#include <stdlib.h>

int count_set_bits(unsigned int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > __UINT32_MAX__) {
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val;
    int result = count_set_bits(num);

    printf("%d\n", result);
    return EXIT_SUCCESS;
}