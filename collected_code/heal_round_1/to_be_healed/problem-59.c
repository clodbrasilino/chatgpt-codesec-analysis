#include<stdio.h>

// Function to find the nth octagonal number
int findNthOctagonalNumber(int n) {
    return 3 * n * (n - 1) + 1;
}

// Main function to test the code
int main() {
    int n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    
    int octagonalNumber = findNthOctagonalNumber(n);
    
    printf("The %dth octagonal number is: %d\n", n, octagonalNumber);
    
    return 0;
}