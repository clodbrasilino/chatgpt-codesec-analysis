#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

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
    size_t len;

    if (printf("Enter a non-negative integer: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(input_buffer, (int)sizeof(input_buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    len = strnlen(input_buffer, sizeof(input_buffer));

    if (len == sizeof(input_buffer)) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return EXIT_FAILURE;
    }

    if (len > 0 && input_buffer[len - 1] == '\n') {
        input_buffer[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    } else if (len > 0 && !feof(stdin)) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
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