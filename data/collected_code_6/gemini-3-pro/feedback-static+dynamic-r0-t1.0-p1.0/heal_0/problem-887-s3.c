#include <stdio.h>
#include <stdbool.h>

bool is_odd(int number) {
    return (number & 1) != 0;
}

int main(void) {
    int number;
    int items_read;

    printf("Enter an integer: ");
    items_read = scanf("%d", &number);

    if (items_read != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return 1;
    }

    if (is_odd(number)) {
        printf("%d is odd.\n", number);
    } else {
        printf("%d is not odd.\n", number);
    }

    return 0;
}