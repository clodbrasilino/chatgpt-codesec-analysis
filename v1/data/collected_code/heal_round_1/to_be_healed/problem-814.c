#include <stdio.h>

float calculateRombusArea(float diagonal1, float diagonal2) {
    float area = (diagonal1 * diagonal2) / 2;
    return area;
}

int main() {
    float diagonal1, diagonal2;

    printf("Enter the length of first diagonal: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'diagonal1' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &diagonal1);

    printf("Enter the length of second diagonal: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'diagonal2' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &diagonal2);

    /* Possible weaknesses found:
     *  Cannot determine that 'diagonal1' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'diagonal2' is initialized [premium-bughuntingUninit]
     */
    float area = calculateRombusArea(diagonal1, diagonal2);

    printf("The area of the rombus is: %.2f", area);

    return 0;
}