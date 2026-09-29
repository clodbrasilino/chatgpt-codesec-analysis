#include <stdio.h>

// Function to check if a number is lucky or not
int isLucky(int n) {
    int counter = 2;
    
    // Iterate until n is 1 or counter exceeds n
    while (n >= counter) {
        // If n is divisible by counter, it is not lucky
        if (n % counter == 0) {
            return 0;
        }
        
        // Reduce n by its first digit and increase counter
        n -= n / counter;
        counter++;
    }
    
    return 1;
}

// Function to print the first n lucky numbers
void printLuckyNumbers(int n) {
    int i, count = 0;
    
    // Iterate until count reaches n
    for (i = 1; count < n; i++) {
        // If i is lucky, print it and increase count
        if (isLucky(i)) {
            printf("%d ", i);
            count++;
        }
    }
}

// Main function
int main() {
    int n;
    
    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    printf("First %d lucky numbers are: ", n);
    printLuckyNumbers(n);
    
    return 0;
}