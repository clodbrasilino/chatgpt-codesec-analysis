#include <stdio.h>
#include <limits.h>

int calculate_dog_years(int human_years) {
    if (human_years <= 2) {
        return human_years * 10;
    } else {
        if (human_years - 2 > INT_MAX / 4) {
            printf("Result exceeds the maximum value of int.\n");
            return -1;
        }
        return 20 + (human_years - 2) * 4;
    }
}

int main() {
    int human_years;
    printf("Enter the dog's age in human years: ");
    if (scanf("%d", &human_years) != 1) {
        printf("Invalid input. Please enter an integer.\n");
        return 1;
    }

    if (human_years < 0) {
        printf("Age cannot be negative.\n");
        return 1;
    }

    int dog_years = calculate_dog_years(human_years);
    if (dog_years == -1) {
        return 1;
    }
    printf("The dog's age in dog years is: %d\n", dog_years);
    return 0;
}