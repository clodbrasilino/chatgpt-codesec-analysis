#include <stdbool.h>
#include <stdio.h>

bool is_even(int num) {
    return (num % 2) == 0;
}

int main() {
    int number = 4;

    if (is_even(number)) {
        printf("The number is even.\n");
    } else {
        printf("The number is odd.\n");
    }

    return 0;
}