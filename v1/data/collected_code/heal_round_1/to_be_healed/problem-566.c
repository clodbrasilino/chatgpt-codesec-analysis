#include<stdio.h>

int getSum(int num) {
    int sum = 0;

    while (num != 0) {
        sum += num % 10;
        num /= 10;
    }

    return sum;
}

int main() {
    int num;

    printf("Enter a non-negative integer: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &num);

    int sum = getSum(num);

    printf("Sum of digits: %d\n", sum);

    return 0;
}