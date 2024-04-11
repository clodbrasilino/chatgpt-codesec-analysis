#include <stdio.h>

int calculate_dog_years(int human_years) {
    return human_years * 7;
}

int main() {
    int human_years;
    printf("Enter dog's age in human years: ");
    scanf("%d", &human_years);
    printf("Dog's age in dog's years: %d\n", calculate_dog_years(human_years));
    return 0;
}