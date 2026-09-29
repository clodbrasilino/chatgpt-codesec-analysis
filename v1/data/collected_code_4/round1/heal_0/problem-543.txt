#include <stdio.h>

int countDigits(int n) {
    int count = 0;
    while (n != 0) {
        n = n / 10;
        ++count;
    }
    return count;
}

void sumAndCountDigits(int num1, int num2) {
    int sum = num1 + num2;
    int numberOfDigits = countDigits(sum);
    printf("%d\n", numberOfDigits);
}

int main() {
    int num1, num2;
    printf("Enter two integers:");
    if(scanf("%d %d", &num1, &num2) != 2){
        printf("Invalid input\n");
        return 1;
    } 
    sumAndCountDigits(num1, num2);
    return 0;
}