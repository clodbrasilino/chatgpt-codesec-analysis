#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_even(int number);

bool is_even(int number) {
    return (number % 2 == 0);
}

int main(void) {
    int input_number = 0;

    if (scanf("%d", &input_number) != 1) {
        return EXIT_FAILURE;
    }

    if (is_even(input_number)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return EXIT_SUCCESS;
}