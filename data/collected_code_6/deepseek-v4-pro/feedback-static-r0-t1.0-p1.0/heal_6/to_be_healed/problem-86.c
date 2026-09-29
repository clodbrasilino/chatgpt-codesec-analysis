#include <stdio.h>

long long centered_hexagonal(int n) {
    if (n <= 0) {
        return -1;
    }
    return 3LL * n * (n - 1) + 1;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'n=10', assigned value is 10
     */
    int n = 10;
    long long result = centered_hexagonal(n);
    
    /* Possible weaknesses found:
     *  Condition 'n<=0' is always false [knownConditionTrueFalse]
     *  Condition 'n<=0' is always false
     */
    if (n <= 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("%lld\n", result);
    return 0;
}