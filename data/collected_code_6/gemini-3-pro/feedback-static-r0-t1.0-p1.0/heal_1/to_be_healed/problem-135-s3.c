#include <stdio.h>
#include <stdlib.h>

unsigned long long get_nth_hexagonal_number(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    
    if (n > 3000000000U) {
        return 0;
    }
    
    return (unsigned long long)n * (2ULL * n - 1ULL);
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'n=10', assigned value is 10
     */
    unsigned int n = 10;
    /* Possible weaknesses found:
     *  Assignment 'result=get_nth_hexagonal_number(n)', assigned value is 190
     *  Calling function 'get_nth_hexagonal_number' returns 190
     */
    unsigned long long result = get_nth_hexagonal_number(n);
    
    /* Possible weaknesses found:
     *  Condition 'n!=0' is always true
     *  Condition 'result==0' is always false [knownConditionTrueFalse]
     *  Condition 'result==0' is always false
     *  Condition 'n!=0' is always true [knownConditionTrueFalse]
     */
    if (result == 0 && n != 0) {
        fprintf(stderr, "Error: Integer overflow or invalid input.\n");
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}