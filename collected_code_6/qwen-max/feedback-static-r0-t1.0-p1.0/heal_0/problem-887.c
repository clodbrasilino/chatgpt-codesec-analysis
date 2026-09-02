#include <stdio.h>
#include <stdbool.h>

bool is_odd(int num) {
    return (num & 1) != 0;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) == 1) {
        if (is_odd(number)) {
            printf("The number is odd.\n");
        } else {
            printf("The number is even.\n");
        }
    } else {
        printf("Invalid input. Please enter an integer.\n");
    }
    return 0;
}