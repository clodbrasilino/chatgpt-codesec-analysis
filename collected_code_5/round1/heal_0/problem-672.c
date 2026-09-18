#include <stdio.h>

int findMax(int num1, int num2, int num3) {
    int max = num1;

    if(num2 > max)
        max = num2;
    if(num3 > max)
        max = num3;

    return max;
}

int main() {
    int num1, num2, num3;

    printf("Enter three numbers: ");
    scanf("%d %d %d", &num1, &num2, &num3);

    int max = findMax(num1, num2, num3);

    printf("Maximum is %d\n", max);

    return 0;
}