#include <stdio.h>
#include <stdlib.h>

int sum_even_odd_difference(int number) {
    int even_sum = 0;
    int odd_sum = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'digit' can be reduced. [variableScope]
     */
    int digit;
    
    number = abs(number);
    
    while (number > 0) {
        digit = number % 10;
        if (digit % 2 == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }
        number /= 10;
    }
    
    return even_sum - odd_sum;
}

int main(void) {
    int number;
    int result;
    
    printf("Enter an integer: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = sum_even_odd_difference(number);
    
    printf("Difference between sum of even and odd digits: %d\n", result);
    
    return EXIT_SUCCESS;
}