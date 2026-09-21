#include <stdio.h>
#include <stdlib.h>

int count_hexadecimal_numbers(unsigned long long start, unsigned long long end) {
    if (start > end) {
        return -1;
    }
    
    unsigned long long total = 0;
    
    if (start == 0) {
        total = 1;
        if (end == 0) {
            return (int)total;
        }
        start = 1;
    }
    
    unsigned long long current = start;
    
    while (current <= end) {
        unsigned long long bits = 64 - __builtin_clzll(current);
        unsigned long long digits = (bits + 3) / 4;
        unsigned long long next_boundary = 1ULL << (digits * 4);
        
        if (next_boundary > end + 1) {
            total += (end - current + 1) * digits;
            break;
        } else {
            total += (next_boundary - current) * digits;
            current = next_boundary;
        }
    }
    
    return (int)total;
}

int main(void) {
    unsigned long long start, end;
    int result;

    if (scanf("%llu", &start) != 1) {
        return EXIT_FAILURE;
    }

    if (scanf("%llu", &end) != 1) {
        return EXIT_FAILURE;
    }

    result = count_hexadecimal_numbers(start, end);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}