#include <stdio.h>
#include <stdlib.h>

int findGCD(int a, int b) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    int temp;
    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(void) {
    int num1 = 0;
    int num2 = 0;
    int gcd = 0;

    if (scanf("%d %d", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }

    if (num1 == 0 && num2 == 0) {
        return EXIT_FAILURE;
    }

    gcd = findGCD(num1, num2);
    printf("%d\n", gcd);

    return EXIT_SUCCESS;
}