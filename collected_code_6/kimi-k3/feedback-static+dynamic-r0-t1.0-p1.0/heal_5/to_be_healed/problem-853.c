#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

long long sum_odd_factors(long long n) {
    long long sum = 0;
    long long i;
    
    if (n <= 0) {
        return 0;
    }
    
    while (n % 2 == 0) {
        n /= 2;
    }
    
    for (i = 1; i <= n / i; i += 2) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:7305,execs:875,op:havoc,rep:12; likely memory-safety defect
  */

int main(void) {
    long long number;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char *endptr;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len > 0 && buffer[len - 1] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    number = strtoll(buffer, &endptr, 10);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer) {
        fprintf(stderr, "No digits found\n");
        return EXIT_FAILURE;
    }
    
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid characters in input\n");
        return EXIT_FAILURE;
    }
    
    if (number <= 0) {
        fprintf(stderr, "Number must be positive\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", sum_odd_factors(number));
    
    return EXIT_SUCCESS;
}