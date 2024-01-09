#include<stdio.h>

// Function to check if a number is lucid
int isLucid(int num) {
    int sum = 0; // Variable to store sum of digits

    // Iterate through each digit of the number
    while (num > 0) {
        int digit = num % 10; // Get the last digit
        sum += digit; // Add the digit to the sum
        num /= 10; // Remove the last digit
    }

    // Check if the sum is divisible by 4 or 7
    if (sum % 4 == 0 || sum % 7 == 0) {
        return 1; // Number is lucid
    } else {
        return 0; // Number is not lucid
    }
}

// Function to get the largest lucid number smaller than or equal to n
int getLucidNumber(int n) {
    // Iterate from n-1 down to 1
    for (int i = n - 1; i >= 1; i--) {
        if (isLucid(i)) {
            return i; // Return the first lucid number found
        }
    }

    return -1; // No lucid number found
}

int main() {
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    int lucid = getLucidNumber(n);

    printf("Largest lucid number smaller than or equal to %d is %d\n", n, lucid);

    return 0;
}
