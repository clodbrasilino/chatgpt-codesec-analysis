#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_odd(int number) {
    return (number & 1) != 0;
}

int main(void) {
    int num;
    int result;

    printf("Enter an integer: ");
    result = scanf("%d", &num);

    if (result != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }

    if (is_odd(num)) {
        printf("%d is odd.\n", num);
    } else {
        printf("%d is even.\n", num);
    }

    return EXIT_SUCCESS;
}