#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    int num1, num2;
    
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    
    if (sscanf(argv[1], "%d", &num1) != 1) {
        return EXIT_FAILURE;
    }
    
    if (sscanf(argv[2], "%d", &num2) != 1) {
        return EXIT_FAILURE;
    }
    
    int result = gcd(num1, num2);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}