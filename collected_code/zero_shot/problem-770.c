#include <stdio.h>

int sumOfFourthPowerOfOddNumbers(int n) {
    int sum = 0;
    int oddNumber = 1;
    
    for (int i = 0; i < n; i++) {
        sum += oddNumber * oddNumber * oddNumber * oddNumber;
        oddNumber += 2;
    }
    
    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    int result = sumOfFourthPowerOfOddNumbers(n);
    printf("The sum of fourth power of first %d odd natural numbers is: %d\n", n, result);
    
    return 0;
}