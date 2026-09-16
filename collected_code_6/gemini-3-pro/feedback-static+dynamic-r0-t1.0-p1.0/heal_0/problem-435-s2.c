#include <stdio.h>
#include <stdlib.h>

int get_last_digit(int num);

int get_last_digit(int num) {
    int last_digit = num % 10;
    
    if (last_digit < 0) {
        last_digit = -last_digit;
    }
    
    return last_digit;
}

int main(void) {
    int number = 0;

    if (scanf("%d", &number) != 1) {
        return EXIT_FAILURE;
    }

    printf("%d\n", get_last_digit(number));

    return EXIT_SUCCESS;
}