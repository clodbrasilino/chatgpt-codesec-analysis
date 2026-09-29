#include <stdio.h>

int calcDogYears(int humanYears) {
    if (humanYears <= 0) {
        return -1;
    } else {
        return humanYears * 7;
    }
}

int main() {
    int humanYears;
    printf("Enter dog's age in human years:\n");
    scanf("%d", &humanYears);

    int dogYears = calcDogYears(humanYears);

    if (dogYears < 0) {
        printf("Invalid input.\n");
    } else {
        printf("Dog's age in dog years: %d\n", dogYears);
    }

    return 0;
}