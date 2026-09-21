#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 16, got <no output>
  *  test case 0 failed: expected 8, got <no output>
  *  test case 2 failed: expected 32, got <no output>
  */

static uint64_t highest_power_of_two(uint64_t number)
{
    if (number == UINT64_C(0)) {
        return UINT64_C(0);
    }

    uint64_t result = UINT64_C(1);

    while (result <= number / UINT64_C(2)) {
        result *= UINT64_C(2);
    }

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    uint64_t number;
    char extra;

    if (fgets(input, sizeof input, stdin) == NULL ||
        sscanf(input, " %" SCNu64 " %c", &number, &extra) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%" PRIu64 "\n", highest_power_of_two(number));
    return 0;
}