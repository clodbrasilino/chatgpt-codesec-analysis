#include <stdio.h>
#include <math.h>

void addAndPrintDigits(int a, int b) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2066381773 + 1999999999 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000005,time:12925,execs:5456,op:havoc,rep:4)
     */
    int sum = a + b;
    /* Possible weaknesses found:
     * UBSan: nan is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:490,execs:227,op:quick,pos:1)
     */
    int digits = (sum == 0) ? 1 : (int) log10((double) sum) + 1;
    printf("Sum: %d, Number of Digits: %d\n", sum, digits);
}

int main() {
    int num1, num2;

    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) return 1;

    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) return 2;

    addAndPrintDigits(num1, num2);

    return 0;
}