#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int check_product_of_two_squares(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    
    for (unsigned int i = 1; i * i <= n; i++) {
        if (n % (i * i) == 0) {
            unsigned int remainder = n / (i * i);
            unsigned int root = (unsigned int)sqrt((double)remainder);
            if (root * root == remainder) {
                return 1;
            }
        }
    }
    
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || val > 4294967295UL) {
        return EXIT_FAILURE;
    }
    
    unsigned int n = (unsigned int)val;
    int result = check_product_of_two_squares(n);
    
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}