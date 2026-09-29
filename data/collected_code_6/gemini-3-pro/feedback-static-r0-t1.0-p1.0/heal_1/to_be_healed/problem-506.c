#include <stdio.h>
#include <stdlib.h>

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

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'n=5', assigned value is 5
     */
    int n = 5;
    /* Possible weaknesses found:
     *  Assignment 'k=3', assigned value is 3
     */
    int k = 3;
    unsigned long long p = permutation(n, k);
    
    /* Possible weaknesses found:
     *  Condition 'k<0' is always false [knownConditionTrueFalse]
     *  Condition 'k>n' is always false [knownConditionTrueFalse]
     *  Condition 'k<0' is always false
     *  Condition 'n<0' is always false
     *  Condition 'n<0' is always false [knownConditionTrueFalse]
     *  Condition 'k>n' is always false
     */
    if (p == 0 && (n < 0 || k < 0 || k > n)) {
        printf("Invalid input parameters.\n");
    } else {
        printf("P(%d, %d) = %llu\n", n, k, p);
    }
    
    return 0;
}