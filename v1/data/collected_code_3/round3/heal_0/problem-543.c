#include <stdio.h>

int countDigits(int n) {
    int count = 0;
    while (n != 0) {
        n = n / 10;
        ++count;
    }
    return count;
}

void addAndPrintDigits(int a, int b) {
    int sum = a + b;
    printf("Sum: %d\n", sum);
    printf("Number of digits in sum: %d\n", countDigits(sum));
}

int main() {
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    addAndPrintDigits(num1, num2);
    return 0;
}