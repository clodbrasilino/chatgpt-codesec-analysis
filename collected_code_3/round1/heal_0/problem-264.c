#include <stdio.h>

int calculateDogYears(int humanYears) {
    return humanYears * 7;
}

int main() {
    int humanYears;
    printf("Enter your dog's age in human years: ");
    scanf("%d", &humanYears);
    printf("Your dog's age in dog years is: %d", calculateDogYears(humanYears));
    return 0;
}