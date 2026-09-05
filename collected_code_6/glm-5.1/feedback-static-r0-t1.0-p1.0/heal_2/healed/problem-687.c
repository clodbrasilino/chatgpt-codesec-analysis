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

int main(int argc, char * const * const argv) {
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