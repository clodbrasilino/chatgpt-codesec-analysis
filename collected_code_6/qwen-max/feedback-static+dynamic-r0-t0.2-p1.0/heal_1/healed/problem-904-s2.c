#include <stdbool.h>
#include <stdio.h>

bool is_even(int num) {
    return (num % 2) == 0;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    if (is_even(number)) {
        printf("The number is even.\n");
    } else {
        printf("The number is odd.\n");
    }

    return 0;
}