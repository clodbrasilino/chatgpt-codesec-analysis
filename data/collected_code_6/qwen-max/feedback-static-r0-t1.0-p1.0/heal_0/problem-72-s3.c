#include <stdio.h>
#include <stdbool.h>

bool can_be_represented_as_difference_of_squares(int n) {
    if (n % 4 == 3) {
        return false;
    } else if (n % 2 == 0 || n > 0) {
        return true;
    }
    return false;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    if (can_be_represented_as_difference_of_squares(number)) {
        printf("The number can be represented as the difference of two squares.\n");
    } else {
        printf("The number cannot be represented as the difference of two squares.\n");
    }

    return 0;
}