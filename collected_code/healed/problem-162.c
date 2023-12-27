#include <stdio.h>

int sumOfPositiveIntegers(int n) {
    int sum = 0;
    int x = 0;
    
    while (n - x > 0) {
        sum += n - x;
        x += 2;
    }
    
    return sum;
}

int main() {
    int n = 0;
    printf("Enter a positive integer: ");
    scanf("%d", &n);
    
    if(n<0){
        printf("Invalid input. Please enter a positive integer.");
        return 0;
    }

    int result = sumOfPositiveIntegers(n);
    
    printf("The sum of the positive integers is: %d\n", result);
    
    return 0;
}