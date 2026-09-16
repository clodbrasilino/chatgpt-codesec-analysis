#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2.5928571428571425, got <no output>
  *  test case 0 failed: expected 2.9289682539682538, got <no output>
  *  test case 1 failed: expected 2.083333333333333, got <no output>
  */

double harmonic_sum(int n)
{
    double sum = 0.0;
    int i;
    
    if (n <= 0) {
        return 0.0;
    }
    
    for (i = n; i >= 1; i--) {
        sum += 1.0 / (double)i;
    }
    
    return sum;
}

int main(void)
{
    char buffer[256];
    char *endptr;
    long value;
    int n;
    double result;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    value = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return EXIT_FAILURE;
    }
    
    n = (int)value;
    
    if (n < 1) {
        return EXIT_FAILURE;
    }
    
    result = harmonic_sum(n);
    
    printf("%.15f\n", result);
    fflush(stdout);
    
    return EXIT_SUCCESS;
}