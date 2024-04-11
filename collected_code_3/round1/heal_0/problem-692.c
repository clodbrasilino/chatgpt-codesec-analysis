#include <stdio.h>

int lastTwoDigitsOfFactorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    if (n == 2)
        return 2;
    if (n == 3)
        return 6;
    if (n == 4)
        return 4;
    return 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Last two digits of factorial of %d is %02d\n", num, lastTwoDigitsOfFactorial(num));
    return 0;
}