#include <stdio.h>

int getSum(int n) {
    int sum = 0;
    while (n != 0) {
        sum = sum + n % 10;
        n = n / 10;
    }
    return sum;
}

int main() {
    int num;
    printf("Enter a non-negative integer: ");
    scanf("%d", &num);
    printf("Sum of digits: %d\n", getSum(num));
    return 0;
}