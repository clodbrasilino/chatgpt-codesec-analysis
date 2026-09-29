#include <stdio.h>
#include <stdlib.h>

int checkProductEquality(long long n) {
    if (n < 0) {
        n = -n;
    }
    
    int evenProd = 1;
    int oddProd = 1;
    int position = 1;
    
    if (n == 0) {
        return 0;
    }
    
    while (n > 0) {
        int digit = n % 10;
        if (position % 2 == 0) {
            evenProd *= digit;
        } else {
            oddProd *= digit;
        }
        position++;
        n /= 10;
    }
    
    return evenProd == oddProd;
}

int main(int argc, char *argv[]) {
    long long num;
    
    if (argc == 2) {
        char *endptr;
        num = strtoll(argv[1], &endptr, 10);
        if (*endptr != '\0') {
            return EXIT_FAILURE;
        }
    } else if (argc == 1) {
        if (scanf("%lld", &num) != 1) {
            return EXIT_FAILURE;
        }
    } else {
        return EXIT_FAILURE;
    }
    
    int result = checkProductEquality(num);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}