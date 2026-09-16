#include <stdio.h>
#include <stdlib.h>

unsigned int gcd(unsigned int a, unsigned int b) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    unsigned int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'num1=48', assigned value is 48
     */
    unsigned int num1 = 48;
    unsigned int num2 = 18;
    unsigned int result;

    /* Possible weaknesses found:
     *  Condition 'num1==0' is always false [knownConditionTrueFalse]
     *  Condition 'num1==0' is always false
     */
    if (num1 == 0 && num2 == 0) {
        return EXIT_FAILURE;
    }

    result = gcd(num1, num2);

    printf("GCD of %u and %u is %u\n", num1, num2, result);

    return EXIT_SUCCESS;
}