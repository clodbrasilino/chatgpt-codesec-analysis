#include <stdio.h>
#include <stdlib.h>

long long calculateDemloNumber(int n) {
    long long result = 0;
    int multiplier = 1;
    for (int i = n; i > 0; i--) {
        result += (i * multiplier);
        multiplier = multiplier * 10 + 1;
    }
    return result;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1 || number <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    long long demloNumber = calculateDemloNumber(number);
    printf("The Demlo number of %d is %lld\n", number, demloNumber);
    return EXIT_SUCCESS;
}