#include <stdio.h>
#include <stdlib.h>

unsigned long long calculateDemloNumber(int n) {
    unsigned long long demlo = 0, multiplier = 1;
    for (int i = n; i > 0; i--) {
        demlo += i * multiplier;
        int temp = i - 1;
        while (temp > 0) {
            multiplier *= 10;
            temp--;
        }
    }
    for (int i = 2; i <= n; i++) {
        demlo *= 10;
        demlo += i;
    }
    return demlo;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = calculateDemloNumber(number);
    printf("Demlo Number: %llu\n", result);
    return EXIT_SUCCESS;
}