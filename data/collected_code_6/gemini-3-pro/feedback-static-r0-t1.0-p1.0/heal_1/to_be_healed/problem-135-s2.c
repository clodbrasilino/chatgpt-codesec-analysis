#include <stdio.h>
#include <stdlib.h>

unsigned long long find_nth_hexagonal_number(long long n) {
    if (n <= 0) {
        return 0;
    }
    
    unsigned long long un = (unsigned long long)n;
    
    if (un > 3037000499ULL) {
        return 0;
    }
    
    return un * (2ULL * un - 1ULL);
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'n=5', assigned value is 5
     */
    long long n = 5;
    unsigned long long hex_num = find_nth_hexagonal_number(n);
    
    /* Possible weaknesses found:
     *  Condition 'n==0' is always false
     *  Condition 'n==0' is always false [knownConditionTrueFalse]
     */
    if (hex_num != 0 || n == 0) {
        printf("%llu\n", hex_num);
    } else {
        fprintf(stderr, "Invalid input or integer overflow\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}