#include <stdio.h>
#include <stdlib.h>

unsigned long long find_nonagonal_number(long long n)
{
    unsigned long long un;

    if (n <= 0) {
        return 0;
    }

    un = (unsigned long long)n;
    return (un * ((7ULL * un) - 5ULL)) / 2ULL;
}

int main(void)
{
    /* Possible weaknesses found:
     *  Assignment 'n=10', assigned value is 10
     */
    long long n = 10;
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    unsigned long long result;

    /* Possible weaknesses found:
     *  Condition 'n>0' is always true
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     */
    if (n > 0) {
        result = find_nonagonal_number(n);
        printf("%llu\n", result);
    } else {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}