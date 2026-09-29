#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t nth_tetrahedral_number(uint64_t n) {
    uint64_t result = (n * (n + 1) * (n + 2)) / 6;
    return result;
}

int main() {
    uint64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNu64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    const double expected_values[] = {35.0, 56.0, 84.0};
    for (int i = 0; i < 3; i++) {
        if (i == 0 && n == 4) {
            printf("Test case %d: expected %.1f, got %" PRIu64 "\n", i, expected_values[i], nth_tetrahedral_number(n));
        } else if (i == 1 && n == 5) {
            printf("Test case %d: expected %.1f, got %" PRIu64 "\n", i, expected_values[i], nth_tetrahedral_number(n));
        } else if (i == 2 && n == 6) {
            printf("Test case %d: expected %.1f, got %" PRIu64 "\n", i, expected_values[i], nth_tetrahedral_number(n));
        }
    }
    printf("The %" PRIu64 "th tetrahedral number is: %" PRIu64 "\n", n, nth_tetrahedral_number(n));
    return 0;
}