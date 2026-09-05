#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t rectangular_number(uint32_t n) {
    return (uint64_t)n * ((uint64_t)n + 1);
}

int main(void) {
    uint32_t n;
    int result;

    printf("Enter n: ");
    result = scanf("%" SCNu32, &n);

    if (result != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%" PRIu64 "\n", rectangular_number(n));

    return 0;
}