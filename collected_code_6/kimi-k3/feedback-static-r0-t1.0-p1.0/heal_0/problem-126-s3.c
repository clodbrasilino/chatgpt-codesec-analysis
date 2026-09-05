#include <stdio.h>
#include <stdlib.h>

int sum_common_divisors(int a, int b) {
    int sum = 0;
    int min = abs(a) < abs(b) ? abs(a) : abs(b);
    
    for (int i = 1; i <= min; i++) {
        if (abs(a) % i == 0 && abs(b) % i == 0) {
            sum += i;
        }
    }
    
    return sum;
}

int main(void) {
    int num1, num2;
    
    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (num1 == 0 && num2 == 0) {
        fprintf(stderr, "Both numbers cannot be zero\n");
        return EXIT_FAILURE;
    }
    
    int result = sum_common_divisors(num1, num2);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}