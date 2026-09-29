#include<stdio.h>

int findNthOctagonalNumber(int n) {
    return 3 * n * (n - 1) + 1;
}

int main() {
    int n = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    int octagonalNumber = findNthOctagonalNumber(n);
    
    printf("The %dth octagonal number is: %d\n", n, octagonalNumber);
    
    return 0;
}