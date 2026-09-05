#include <stdio.h>
#include <stdlib.h>

int find_difference(int num) {
    int even_sum = 0;
    int odd_sum = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'digit' can be reduced. [variableScope]
     */
    int digit;
    
    num = abs(num);
    
    while (num > 0) {
        digit = num % 10;
        if (digit % 2 == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }
        num /= 10;
    }
    
    return even_sum - odd_sum;
}

int main(void) {
    int num;
    
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Difference: %d\n", find_difference(num));
    
    return EXIT_SUCCESS;
}