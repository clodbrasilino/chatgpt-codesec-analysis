#include <stdio.h>

unsigned long long get_nth_octagonal_number(int n) {
    unsigned long long un;
    
    if (n <= 0) {
        return 0;
    }
    
    un = (unsigned long long)n;
    return un * ((3ULL * un) - 2ULL);
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'n=10', assigned value is 10
     */
    int n = 10;
    unsigned long long result;

    /* Possible weaknesses found:
     *  Condition 'n<=0' is always false
     *  Condition 'n<=0' is always false [knownConditionTrueFalse]
     */
    if (n <= 0) {
        return 1;
    }

    result = get_nth_octagonal_number(n);
    printf("%llu\n", result);

    return 0;
}