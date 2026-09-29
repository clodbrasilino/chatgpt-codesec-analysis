#include <stdio.h>
#include <stdlib.h>

int count_set_bits(unsigned int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
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

    unsigned long val = strtoul(argv[1], NULL, 10);
    if (val > __UINT32_MAX__) {
        return EXIT_FAILURE;
    }

    unsigned int num = (unsigned int)val;
    int result = count_set_bits(num);
    
    printf("%d\n", result);
    return EXIT_SUCCESS;
}