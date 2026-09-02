#include <stdio.h>
#include <stdbool.h>

bool isCoPrime(int a, int b) {
    int min = (a < b) ? a : b;
    for (int i = 2; i <= min; i++) {
        if (a % i == 0 && b % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    if (isCoPrime(num1, num2)) {
        printf("The numbers are co-prime.\n");
    } else {
        printf("The numbers are not co-prime.\n");
    }
    return 0;
}