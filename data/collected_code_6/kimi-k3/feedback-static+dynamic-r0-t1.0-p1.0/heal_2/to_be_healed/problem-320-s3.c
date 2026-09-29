#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long calculate_difference(long long n) {
    long long sum = (n * (n + 1)) / 2;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 6172882716 * 6172882716 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000007,time:5294,execs:1781,op:havoc,rep:3)
     */
    long long squared_sum = sum * sum;
    long long sum_of_squares = (n * (n + 1) * (2 * n + 1)) / 6;
    return squared_sum - sum_of_squares;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:887,execs:339,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[128];
    char *end_ptr = NULL;
    long long n = 0;
    long long result = 0;

    printf("Enter a natural number (n): ");

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoll(input_buffer, &end_ptr, 10);

    if (errno == ERANGE || n <= 0) {
        fprintf(stderr, "Error: Input must be a positive natural number within valid range.\n");
        return EXIT_FAILURE;
    }

    if (end_ptr == input_buffer || (*end_ptr != '\n' && *end_ptr != '\0')) {
        fprintf(stderr, "Error: Invalid input format. Please enter a valid integer.\n");
        return EXIT_FAILURE;
    }

    if (n > 1000000) {
        fprintf(stderr, "Error: Input too large, calculation would exceed integer limits.\n");
        return EXIT_FAILURE;
    }

    result = calculate_difference(n);
    printf("Difference: %lld\n", result);

    return EXIT_SUCCESS;
}