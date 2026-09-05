#include <stdio.h>
#include <stdlib.h>

unsigned int find_gcd(unsigned int a, unsigned int b) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    unsigned int temp;
    
    if (a == 0 && b == 0) {
        exit(EXIT_FAILURE);
    }
    
    if (a == 0) {
        return b;
    }
    
    if (b == 0) {
        return a;
    }
    
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}

int main(void) {
    unsigned int a;
    unsigned int b;
    
    if (scanf("%u %u", &a, &b) != 2) {
        return EXIT_FAILURE;
    }
    
    printf("%u\n", find_gcd(a, b));
    
    return EXIT_SUCCESS;
}