#include <stdio.h>

int countEqualNumbers(int num1, int num2, int num3) {
    int count = 0;
    if (num1 == num2) {
        count++;
    }
    if (num1 == num3) {
        count++;
    }
    if (num2 == num3) {
        count++;
    }
    return count;
}

int main() {
    int num1, num2, num3;
    printf("Enter three integers: ");
    scanf("%d %d %d", &num1, &num2, &num3);
    int equalCount = countEqualNumbers(num1, num2, num3);
    printf("Number of equal numbers: %d\n", equalCount);
    return 0;
}