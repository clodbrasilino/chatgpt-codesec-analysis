#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool is_valid_dimension(long val) {
    return val >= 0;
}

uint64_t count_squares(uint64_t width, uint64_t height) {
    if (!is_valid_dimension(width) || !is_valid_dimension(height)) return 0;
    uint64_t smaller = width < height ? width : height;
    uint64_t larger = width > height ? width : height;
    uint64_t total = 0;
    for (uint64_t i = 1; i <= smaller; ++i)
        total += (larger - i + 1) * (smaller - i + 1);
    return total;
}

int main() {
    long width, height;
    if (scanf("%ld %ld", &width, &height) != 2) return 1;
    uint64_t result = count_squares((uint64_t)width, (uint64_t)height);
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("%llu\n", result);
    return 0;
}