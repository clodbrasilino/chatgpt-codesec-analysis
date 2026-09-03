#include <stdio.h>
#include <stdbool.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    int number;
    printf("Enter an integer: ");
    if (scanf("%d", &number) != 1) {
        return 1;
    }
    printf("%s\n", is_even(number) ? "true" : "false");
    return 0;
}