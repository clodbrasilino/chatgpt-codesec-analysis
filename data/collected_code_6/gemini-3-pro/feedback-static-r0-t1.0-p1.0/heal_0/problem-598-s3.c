#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int isArmstrong(int num) {
    if (num < 0) {
        return 0;
    }

    int originalNum = num;
    int remainder = 0;
    int result = 0;
    int n = 0;

    int temp = num;
    while (temp != 0) {
        temp /= 10;
        ++n;
    }

    temp = num;
    while (temp != 0) {
        remainder = temp % 10;
        result += pow(remainder, n);
        temp /= 10;
    }

    if (result == originalNum) {
        return 1;
    } else {
        return 0;
    }
}

int main(void) {
    int num;
    int scanResult = scanf("%d", &num);

    if (scanResult != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (isArmstrong(num)) {
        printf("%d is an Armstrong number.\n", num);
    } else {
        printf("%d is not an Armstrong number.\n", num);
    }

    return EXIT_SUCCESS;
}