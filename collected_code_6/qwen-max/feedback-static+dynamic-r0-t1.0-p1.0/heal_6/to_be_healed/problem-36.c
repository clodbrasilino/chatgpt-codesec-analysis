#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 6, got <no output>
  *  test case 0 failed: expected 5, got <no output>
  *  test case 2 failed: expected 3, got <no output>
  */

int find_nth_digit(int numerator, int denominator, int n) {
    long long remainder = numerator;
    int digit = 0;
    for (int i = 0; i < n; ++i) {
        remainder *= 10;
        digit = remainder / denominator;
        remainder %= denominator;
    }
    return digit;
}

int main() {
    /* Possible weaknesses found:
     *  Assignment 'n=5', assigned value is 5
     *  The scope of the variable 'numerator' can be reduced. [variableScope]
     *  The scope of the variable 'result' can be reduced. [variableScope]
     *  The scope of the variable 'denominator' can be reduced. [variableScope]
     */
    int result, numerator = 1, denominator = 7, n = 5;
    /* Possible weaknesses found:
     *  Condition 'n>0' is always true
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     */
    if (n > 0) {
        result = find_nth_digit(numerator, denominator, n);
        printf("The %dth digit of the fraction %d/%d is: %d\n", n, numerator, denominator, result);
    } else {
        printf("Invalid input: n must be greater than 0.\n");
    }
    return 0;
}