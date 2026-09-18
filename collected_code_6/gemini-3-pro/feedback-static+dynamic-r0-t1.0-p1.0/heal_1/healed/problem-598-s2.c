#include <stdio.h>
#include <stdlib.h>

int isArmstrong(int num) {
    if (num < 0) {
        return 0;
    }

    int originalNum = num;
    long long sum = 0;
    int digits = 0;

    int temp = num;
    while (temp != 0) {
        digits++;
        temp /= 10;
    }

    temp = num;
    while (temp != 0) {
        int remainder = temp % 10;
        long long power = 1;
        for (int i = 0; i < digits; i++) {
            power *= remainder;
        }
        sum += power;
        temp /= 10;
    }

    return (sum == (long long)originalNum);
}

int main(void) {
    int num;

    if (scanf("%d", &num) != 1) {
        return EXIT_FAILURE;
    }

    if (isArmstrong(num)) {
        printf("Armstrong\n");
    } else {
        printf("Not Armstrong\n");
    }

    return EXIT_SUCCESS;
}