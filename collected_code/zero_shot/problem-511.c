#include <stdio.h>

// Function to calculate the sum of factors
int findMinSumOfFactors(int number) {
    int sum = 0;
    int i = 1;

    // Iterate through all the numbers from 1 to number
    while(i <= number) {

        // Check if i is a factor of the given number
        if(number % i == 0) {

            // Add i to the sum
            sum += i;
        }
        i++;
    }
    return sum;
}

// Test the function
int main() {
    int number = 12;
    int minSumOfFactors = findMinSumOfFactors(number);

    // Print the result
    printf("Minimum sum of factors of %d is %d\n", number, minSumOfFactors);

    return 0;
}