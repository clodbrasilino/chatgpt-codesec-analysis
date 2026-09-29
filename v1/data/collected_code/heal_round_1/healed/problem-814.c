#include <stdio.h>

float calculateRombusArea(float diagonal1, float diagonal2) {
    float area = (diagonal1 * diagonal2) / 2;
    return area;
}

int main() {
    float diagonal1 = 0.0, diagonal2 = 0.0;

    printf("Enter the length of first diagonal: ");
    scanf("%f", &diagonal1);

    printf("Enter the length of second diagonal: ");
    scanf("%f", &diagonal2);

    float area = calculateRombusArea(diagonal1, diagonal2);

    printf("The area of the rombus is: %.2f", area);

    return 0;
}