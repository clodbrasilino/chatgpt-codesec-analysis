#include <stdio.h>

int calculate_area(int base, int height) {
    int area = base * height;
    return area;
}

int main() {
    int base, height;
    printf("Enter the base of the parallelogram: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'base' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &base);
    printf("Enter the height of the parallelogram: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'height' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &height);
    int area = calculate_area(base, height);
    printf("The area of the parallelogram is: %d", area);
    return 0;
}