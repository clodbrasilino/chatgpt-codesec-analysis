#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2.5928571428571425, got <no output>
  *  test case 0 failed: expected 2.9289682539682538, got <no output>
  *  test case 1 failed: expected 2.083333333333333, got <no output>
  */

double harmonic_sum(int n) {
    double sum = 0.0;
    double current = 1.0;
    int i;
    
    if (n <= 1) {
        return 0.0;
    }
    
    for (i = 1; i < n; i++) {
        sum += current / (double)i;
    }
    
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    long val;
    int n;
    char *endptr;
    size_t len;
    int c;
    
    printf("Enter n: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    
    if (len == sizeof(buffer)) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || *endptr != '\0' || endptr == buffer) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (val > INT_MAX || val < 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    n = (int)val;
    
    if (n > 1000000) {
        fprintf(stderr, "Value too large\n");
        return 1;
    }
    
    printf("Harmonic sum of %d-1 = %.15f\n", n, harmonic_sum(n));
    
    return 0;
}