#include <stdio.h>
#include <math.h>
#include <stdint.h>

uint64_t next_perfect_square(uint64_t n) {
    uint64_t root = (uint64_t)sqrt(n);
    if (root * root == n) {
        root += 1;
    }
    return root * root;
}

int main() {
    uint64_t number;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long *' but the argument type is 'unsigned long *'. [invalidScanfArgType_int]
     */
    if (scanf("%llu", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    uint64_t next_square = next_perfect_square(number);
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("Next perfect square: %llu\n", next_square);
    return 0;
}