#include <stdio.h>
#include <stdlib.h>

int find_last_digit(int number) {
    return abs(number % 10);
}

int main(void) {
    int number = 0;
    int result = 0;
    
    printf("Enter an integer: ");
    
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = find_last_digit(number);
    printf("Last digit: %d\n", result);
    
    return EXIT_SUCCESS;
}