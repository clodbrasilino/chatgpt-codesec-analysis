#include <stdio.h>
#include <stdlib.h>

int multiply(int a, int b);

int multiply(int a, int b) {
    unsigned int ua = (unsigned int)a;
    unsigned int ub = (unsigned int)b;
    unsigned int result = 0;

    while (ub != 0) {
        if (ub & 1) {
            result += ua;
        }
        ua <<= 1;
        ub >>= 1;
    }

    return (int)result;
}

int main(void) {
    int num1 = 15;
    int num2 = -42;
    int result = 0;

    result = multiply(num1, num2);
    printf("%d\n", result);

    return 0;
}