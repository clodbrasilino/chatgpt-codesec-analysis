#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2, got <no output>
  *  test case 1 failed: expected 1, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  */

unsigned int count_set_bits(unsigned int n)
{
    unsigned int count = 0;
    while (n != 0U) {
        n &= (n - 1U);
        count++;
    }
    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[128];
    char *end_ptr = NULL;
    unsigned long parsed_value;
    unsigned int number;

    if (printf("Enter a non-negative integer: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtoul(input_buffer, &end_ptr, 10);

    if (end_ptr == input_buffer) {
        return EXIT_FAILURE;
    }

    if (errno == ERANGE || parsed_value > UINT_MAX) {
        return EXIT_FAILURE;
    }

    number = (unsigned int)parsed_value;

    if (printf("Number of set bits: %u\n", count_set_bits(number)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}