#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int are_coprime(int num1, int num2) {
    if (num1 == 0 && num2 == 0) {
        return 0;
    }
    return gcd(num1, num2) == 1;
}

int main(void) {
    int num1, num2;
    int result;

    printf("Enter two integers: ");
    result = scanf("%d %d", &num1, &num2);

    if (result != 2) {
        printf("Invalid input. Please enter two integers.\n");
        return EXIT_FAILURE;
    }

    if (are_coprime(num1, num2)) {
        printf("%d and %d are co-prime.\n", num1, num2);
    } else {
        printf("%d and %d are not co-prime.\n", num1, num2);
    }

    return EXIT_SUCCESS;
}