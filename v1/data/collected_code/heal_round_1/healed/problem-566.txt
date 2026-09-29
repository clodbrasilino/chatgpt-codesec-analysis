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
    int num = 0;

    printf("Enter a non-negative integer: ");
    scanf("%d", &num);

    if(num<0){
        printf("Invalid input");
        return 1;
    }

    int sum = getSum(num);

    printf("Sum of digits: %d\n", sum);

    return 0;
}