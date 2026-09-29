#include <stdio.h>
#include <stdbool.h>

bool is_even(int num) {
    return (num % 2) == 0;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input. Please enter an integer.\n");
        return 1;
    }
    if (is_even(number)) {
        puts("True");
    } else {
        puts("False");
    }
    return 0;
}