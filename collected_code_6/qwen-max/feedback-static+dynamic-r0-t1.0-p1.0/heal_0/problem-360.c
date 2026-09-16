#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

uint64_t calculate_nth_carol_number(int n) {
    uint64_t value = 1;
    for (int i = 1; i <= n; ++i) {
        value = (value - 1) * 2 + 1;
        value *= value - 2;
    }
    return value;
}

int main() {
    int n;
    printf("Enter the order of Carol number: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        fprintf(stderr, "Please enter a valid positive integer.\n");
        return EXIT_FAILURE;
    }

    uint64_t carol_number = calculate_nth_carol_number(n);
    printf("The %d-th Carol number is: %" PRIu64 "\n", n, carol_number);

    return EXIT_SUCCESS;
}