#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

int sum_and_average(int n, long long *sum, double *average)
{
    if (n < 1 || sum == NULL || average == NULL) {
        return -1;
    }

    if ((long long)n > (LLONG_MAX / (long long)(n + 1)) / 2) {
        return -1;
    }

    *sum = (long long)n * (long long)(n + 1) / 2LL;
    *average = (double)*sum / (double)n;
    
    return 0;
}

int main(void)
{
    int n;
    long long sum;
    double average;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    long val;
    size_t len;

    printf("Enter a positive integer: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
    len = strlen(buffer);
    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer || (*endptr != '\n' && *endptr != '\0') || val < 1 || val > INT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    n = (int)val;

    if (sum_and_average(n, &sum, &average) != 0) {
        fprintf(stderr, "Calculation failed\n");
        return EXIT_FAILURE;
    }

    printf("Sum of first %d natural numbers: %lld\n", n, sum);
    printf("Average: %.2f\n", average);

    return EXIT_SUCCESS;
}