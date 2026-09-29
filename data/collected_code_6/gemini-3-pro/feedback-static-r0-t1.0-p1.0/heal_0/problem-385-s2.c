#include <stdio.h>
#include <stdlib.h>

long long get_perrin_number(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 3;
    }
    if (n == 1) {
        return 0;
    }
    if (n == 2) {
        return 2;
    }
    return get_perrin_number(n - 2) + get_perrin_number(n - 3);
}

int main(void) {
    int n = 10;
    long long result = get_perrin_number(n);
    
    if (result == -1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Perrin number at position %d is %lld\n", n, result);
    return EXIT_SUCCESS;
}