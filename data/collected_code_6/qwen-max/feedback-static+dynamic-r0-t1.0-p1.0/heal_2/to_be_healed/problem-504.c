#include <stdio.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  'PRIu64' is defined in header '<inttypes.h>'; this is probably fixable by adding '#include <inttypes.h>'
  */

uint64_t cube_sum(uint32_t n) {
    uint64_t sum = 0;
    for (uint32_t i = 1; i <= n; ++i) {
        sum += (uint64_t)i * i * i;
    }
    return sum;
}

int main() {
    uint32_t n;
    printf("Enter a natural number: ");
    if (scanf("%u", &n) == 1) {
        uint64_t result = cube_sum(n);
        /* Possible weaknesses found:
         *  expected ')' before 'PRIu64'
         *  to match this '('
         *  expected ')'
         */
        printf("The cube sum of first %u natural numbers is: %" PRIu64 "\n", n, result);
    } else {
        fprintf(stderr, "Invalid input. Please enter a natural number.\n");
    }
    return 0;
}