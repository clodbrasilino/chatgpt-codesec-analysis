#include<stdio.h>

int sum_of_fifth_power(int n) {
    int sum = 0;
    int num = 2;
    for (int i = 1; i <= n; i++) {
        sum += num * num * num * num * num;
        num += 2;
    }
    return sum;
}

int main() {
    int n = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    if(n < 0) {
        printf("Value of n cannot be negative. Please enter a valid number.\n");
        return 0;
    }

    int result = sum_of_fifth_power(n);
    printf("The sum of the fifth power of the first %d even natural numbers is: %d\n", n, result);

    return 0;
}