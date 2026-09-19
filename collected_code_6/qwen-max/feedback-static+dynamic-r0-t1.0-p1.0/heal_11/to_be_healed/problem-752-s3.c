#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 1, got 2
  *  test case 0 failed: expected 11, got 29
  *  test case 2 failed: expected 5, got 12
  */

uint64_t jacobsthal(uint64_t n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    uint64_t a = 0, b = 1;
    for (uint64_t i = 2; i <= n; ++i) {
        uint64_t c = a + 2 * b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    char input[16];
    printf("Enter the value of n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    char *endptr;
    uint64_t n = strtoull(input, &endptr, 10);
    if (*endptr != '\0' && *endptr != '\n' || endptr == input) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("The %" PRIu64 "th Jacobsthal number is: %" PRIu64 "\n", n, jacobsthal(n));
    return 0;
}