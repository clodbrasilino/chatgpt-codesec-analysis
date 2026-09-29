#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

long long sum_of_cubes(int n) {
    long long sum = 0;
    int i;
    
    if (n < 1) {
        return 0;
    }
    
    for (i = 1; i <= n; i++) {
        long long cube = (long long)i * i * i;
        if (sum > LLONG_MAX - cube) {
            return -1;
        }
        sum += cube;
    }
    
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *endptr;
    long input_val;
    int n;
    long long result;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    if (buffer[0] == '\0') {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    input_val = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    if (input_val < 1 || input_val > INT_MAX) {
        fprintf(stderr, "Input out of valid range\n");
        return EXIT_FAILURE;
    }
    
    n = (int)input_val;
    result = sum_of_cubes(n);
    
    if (result == -1) {
        fprintf(stderr, "Integer overflow occurred\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}