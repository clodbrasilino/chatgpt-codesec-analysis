#include <stdio.h>

int getSum(int n){
    int sum = 0;
    while (n != 0){
        sum = sum + n % 10;
        n = n / 10;
    }
    return sum;
}

int main(){
    int number, result;

    printf("Enter a non-negative integer: ");
    scanf("%d", &number);

    if (number < 0){
        printf("Invalid input! Make sure you enter a non-negative integer.");
        return 1;
    }

    result = getSum(number);
    printf("Sum of digits: %d\n", result);

    return 0;
}