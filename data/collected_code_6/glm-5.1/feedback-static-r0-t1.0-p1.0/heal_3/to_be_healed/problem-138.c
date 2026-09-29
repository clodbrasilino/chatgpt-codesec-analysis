#include <stdio.h>
#include <stdlib.h>

int check_sum_non_zero_powers(int num) {
    if (num <= 0) {
        return 0;
    }
    num = num & (num - 1);
    if (num == 0) {
        return 0;
    }
    num = num & (num - 1);
    if (num == 0) {
        return 1;
    }
    return 0;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    long val = strtol(argv[1], NULL, 10);
    if (val > 1000000000 || val < -1000000000) {
        fprintf(stderr, "Out of range\n");
        return EXIT_FAILURE;
    }
    
    int num = (int)val;
    int result = check_sum_non_zero_powers(num);
    
    printf("%d\n", result);
    return EXIT_SUCCESS;
}