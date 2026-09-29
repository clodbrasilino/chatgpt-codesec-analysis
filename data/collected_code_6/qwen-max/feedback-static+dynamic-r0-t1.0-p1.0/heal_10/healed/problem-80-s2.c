#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

uint64_t nth_tetrahedral_number(uint64_t n) {
    return (n * (n + 1) * (n + 2)) / 6;
}

int main() {
    uint64_t n;
    printf("Enter the value of n: ");
    int scan_result = scanf("%" SCNu64, &n);
    while (getchar() != '\n' && scan_result == 1);
    if (scan_result != 1 || n < 0) {
        while (getchar() != '\n');
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return 1;
    }
    uint64_t result = nth_tetrahedral_number(n);
    printf("The %" PRIu64 "th tetrahedral number is: %" PRIu64 "\n", n, result);
    return 0;
}