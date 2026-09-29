#include <stdio.h>
#include <math.h>

int canBeSumOfTwoSquares(int num) {
    if (num < 0) return 0; 
    for (int i = 0; i <= sqrt(num); i++) { 
        int root = sqrt(num - i * i); 
        if (root * root + i * i == num) {
            return 1; 
        }
    }
    return 0; 
} 

int main() {
    int num;
    printf("Enter a number:\n");
    scanf("%d", &num);
    if (canBeSumOfTwoSquares(num)) {
        printf("Yes, the number can be represented as a sum of two squares.\n"); 
    } else {
        printf("No, the number cannot be represented as a sum of two squares.\n"); 
    }
    return 0;
} 