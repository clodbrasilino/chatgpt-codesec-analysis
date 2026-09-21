#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long reverse_number(int n) {
    long long rev = 0;
    int num = abs(n);
    while (num > 0) {
        rev = rev * 10 + num % 10;
        num /= 10;
    }
    return (n < 0) ? -rev : rev;
}

int check_one_less_than_twice_reverse(int n) {
    long long rev = reverse_number(n);
    if ((n < 0 && rev > (INT_MIN + 1) / 2) || (n > 0 && rev < (INT_MAX - 1) / 2)) {
        return n == (2 * rev) - 1;
    }
    return 0;
}

int main(int argc, char * const * const argv) {
    int n;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    long long val = strtoll(argv[1], NULL, 10);
    if (val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    n = (int)val;
    
    if (check_one_less_than_twice_reverse(n)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return EXIT_SUCCESS;
}