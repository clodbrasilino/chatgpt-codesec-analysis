#include <stdio.h>

int exponentiation(int base, int power) {
    int result = 1;
    for (int i = 0; i < power; i++) {
        result *= base;
    }
    return result;
}

int main() {
    int base = 0, power = 0;

    printf("Enter the base: ");
    scanf("%d", &base);

    printf("Enter the power: ");
    scanf("%d", &power);

    int result = exponentiation(base, power);
    printf("The result is: %d\n", result);

    return 0;
}