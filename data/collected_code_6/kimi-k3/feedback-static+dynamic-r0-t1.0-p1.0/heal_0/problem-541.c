#include <stdio.h>
#include <stdlib.h>

int is_abundant(int number) {
    int sum = 0;
    int i;
    
    if (number <= 0) {
        return 0;
    }
    
    for (i = 1; i <= number / 2; i++) {
        if (number % i == 0) {
            sum += i;
        }
    }
    
    return sum > number;
}

int main(void) {
    int number;
    int result;
    
    printf("Enter a positive integer: ");
    result = scanf("%d", &number);
    
    if (result != 1) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (is_abundant(number)) {
        printf("%d is an abundant number\n", number);
    } else {
        printf("%d is not an abundant number\n", number);
    }
    
    return EXIT_SUCCESS;
}