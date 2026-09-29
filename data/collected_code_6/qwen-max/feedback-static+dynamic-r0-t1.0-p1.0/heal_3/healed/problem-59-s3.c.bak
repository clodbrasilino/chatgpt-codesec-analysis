#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

bool is_valid_input(int64_t n) {
    if (n < 0) return false;
    int64_t max_n = (1LL << 32) - 1; // Prevent overflow by limiting n
    if (n > max_n) return false;
    return true;
}

int64_t nth_octagonal_number(int64_t n) {
    return 3 * n * n - 2 * n;
}

int main() {
    int64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNd64, &n) != 1 || !is_valid_input(n)) {
        printf("Invalid input\n");
        return 1;
    }
    int64_t result = nth_octagonal_number(n);
    printf("The %" PRId64 "th octagonal number is: %" PRId64 "\n", n, result);
    return 0;
}