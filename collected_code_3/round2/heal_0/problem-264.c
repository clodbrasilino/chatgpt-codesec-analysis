#include <stdio.h>

int calculateDogYears(int humanYears) {
    return humanYears * 7;
}

int main() {
    int humanYears;
    printf("Enter dog's age in human years: ");
    scanf("%d", &humanYears);
    printf("Dog's age in dog's years: %d", calculateDogYears(humanYears));
    return 0;
}