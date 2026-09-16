#include <stdio.h>
#include <stdlib.h>

int getLastDigit(int num) {
    if (num < 0) {
        num = -num;
    }
    return num % 10;
}

int main(void) {
    int number;
    int lastDigit;

    if (scanf("%d", &number) != 1) {
        return EXIT_FAILURE;
    }

    lastDigit = getLastDigit(number);
    printf("%d\n", lastDigit);

    return EXIT_SUCCESS;
}