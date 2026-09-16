#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long sum_fourth_power_odd(int n)
{
    unsigned long long sum = 0ULL;
    int i;
    /* Possible weaknesses found:
     *  The scope of the variable 'odd' can be reduced. [variableScope]
     */
    unsigned long long odd;
    /* Possible weaknesses found:
     *  The scope of the variable 'fourth' can be reduced. [variableScope]
     */
    unsigned long long fourth;
    
    if (n <= 0) {
        return 0ULL;
    }
    
    for (i = 0; i < n; i++) {
        odd = (unsigned long long)(2 * i + 1);
        fourth = odd * odd * odd * odd;
        
        if (ULLONG_MAX - sum < fourth) {
            return 0ULL;
        }
        sum += fourth;
    }
    
    return sum;
}

int main(void)
{
    char buffer[256];
    char *endptr;
    long val;
    int n;
    unsigned long long result;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return EXIT_FAILURE;
    }
    
    if (val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    
    result = sum_fourth_power_odd(n);
    
    if (result == 0ULL && n > 0) {
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}