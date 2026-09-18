#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int calculate_dog_years(int human_years) {
    if (human_years <= 2) {
        long long result = (long long)human_years * 10.5 + 0.5;
        if (result > INT_MAX || result < INT_MIN) {
            return -1;
        }
        return (int)result;
    } else {
        long long temp = (long long)(human_years - 2) * 4;
        if (temp > INT_MAX - 21 || temp < INT_MIN) {
            return -1;
        }
        return 21 + (int)temp;
    }
}

int main() {
    int human_years;
    printf("Enter the age of the dog in human years: ");
    if (scanf("%d", &human_years) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    int dog_years = calculate_dog_years(human_years);
    if (dog_years == -1) {
        printf("Result out of range for 'int' type.\n");
    } else {
        printf("The dog's age in dog years is: %d\n", dog_years);
    }
    return 0;
}