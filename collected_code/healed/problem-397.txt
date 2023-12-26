#include <stdio.h>

float findMedian(float num1, float num2, float num3) {
    if ((num1 > num2 && num1 < num3) || (num1 < num2 && num1 > num3)) {
        return num1;
    } else if ((num2 > num1 && num2 < num3) || (num2 < num1 && num2 > num3)) {
        return num2;
    } else {
        return num3;
    }
}

int main() {
    float num1 = 0, num2 = 0, num3 = 0, median;
    printf("Enter three numbers: ");
    scanf("%f %f %f", &num1, &num2, &num3);

    median = findMedian(num1, num2, num3);
    printf("The median is: %.2f", median);

    return 0;
}