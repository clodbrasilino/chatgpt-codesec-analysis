#include <stdio.h>
#include <stdlib.h>

int last_digit(int num) {
    return abs(num % 10);
}

int main(void) {
    int number;
    
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Last digit: %d\n", last_digit(number));
    
    return 0;
}