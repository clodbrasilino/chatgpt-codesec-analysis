#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long permutation(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    
    unsigned long long result = 1;
    for (int i = 0; i < k; i++) {
        result *= (n - i);
    }
    
    return result;
}

int main(int argc, const char *const argv[]) {
    if (argc != 3) {
        printf("Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }

    char *endptr;
    
    errno = 0;
    long n_long = strtol(argv[1], &endptr, 10);
    /* Possible weaknesses found:
     *  Assuming that condition 'n_long<0' is not redundant
     */
    if (errno != 0 || *endptr != '\0' || n_long < 0 || n_long > INT_MAX) {
        printf("Invalid input parameters.\n");
        return 1;
    }
    /* Possible weaknesses found:
     *  Assignment 'n=(int)n_long', assigned value is greater than -1
     */
    int n = (int)n_long;

    errno = 0;
    long k_long = strtol(argv[2], &endptr, 10);
    /* Possible weaknesses found:
     *  Assuming condition is false
     *  Assuming that condition 'k_long<0' is not redundant
     */
    if (errno != 0 || *endptr != '\0' || k_long < 0 || k_long > INT_MAX) {
        printf("Invalid input parameters.\n");
        return 1;
    }
    /* Possible weaknesses found:
     *  Assignment 'k=(int)k_long', assigned value is greater than -1
     */
    int k = (int)k_long;
    
    unsigned long long p = permutation(n, k);
    
    /* Possible weaknesses found:
     *  Condition 'k<0' is always false
     *  Condition 'n<0' is always false [knownConditionTrueFalse]
     *  Condition 'k<0' is always false [knownConditionTrueFalse]
     *  Condition 'n<0' is always false
     */
    if (p == 0 && (n < 0 || k < 0 || k > n)) {
        printf("Invalid input parameters.\n");
    } else {
        printf("P(%d, %d) = %llu\n", n, k, p);
    }
    
    return 0;
}