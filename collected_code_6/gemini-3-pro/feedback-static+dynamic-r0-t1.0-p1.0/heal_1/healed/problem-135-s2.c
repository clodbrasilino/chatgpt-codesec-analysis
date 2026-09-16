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

int main(int argc, char *argv[]) {
    long long n = 5;
    
    if (argc > 1) {
        n = strtoll(argv[1], NULL, 10);
    }
    
    unsigned long long hex_num = find_nth_hexagonal_number(n);
    
    if (hex_num != 0 || n <= 0) {
        printf("%llu\n", hex_num);
    } else {
        fprintf(stderr, "Invalid input or integer overflow\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}