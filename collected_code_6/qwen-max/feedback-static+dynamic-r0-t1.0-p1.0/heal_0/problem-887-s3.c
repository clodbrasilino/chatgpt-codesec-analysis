#include <stdio.h>
#include <stdbool.h>

bool is_odd(int num) {
    return (num & 1) == 1;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
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