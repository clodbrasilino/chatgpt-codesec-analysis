#include <stdio.h>
#include <limits.h>

unsigned long long sum_of_squares_of_even(int n) {
    if (n <= 0) {
        return 0;
    }

    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (sum > ULLONG_MAX - (unsigned long long)4 * i * i) {
            return 0;
        }
        sum += (unsigned long long)4 * i * i;
    }

    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'n=5', assigned value is 5
     */
    int n = 5;
    unsigned long long result = sum_of_squares_of_even(n);
    
    /* Possible weaknesses found:
     *  Condition 'n>0' is always true
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     */
    if (result == 0 && n > 0) {
        printf("Overflow occurred.\n");
        return 1;
    }
    
    printf("%llu\n", result);
    return 0;
}