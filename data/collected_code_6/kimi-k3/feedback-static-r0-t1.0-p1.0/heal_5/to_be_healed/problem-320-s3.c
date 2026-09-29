#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

long long calculate_difference(long long n) {
    long long sum = (n * (n + 1)) / 2;
    long long squared_sum = sum * sum;
    long long sum_of_squares = (n * (n + 1) * (2 * n + 1)) / 6;
    return squared_sum - sum_of_squares;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[128];
    char *end_ptr = NULL;
    long long n = 0;
    long long result = 0;
    size_t len = 0;

    printf("Enter a natural number (n): ");

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
    len = strlen(input_buffer);
    if (len > 0 && input_buffer[len - 1] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Error: Input too long.\n");
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