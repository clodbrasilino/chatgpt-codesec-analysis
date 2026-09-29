#include <stdbool.h>
#include <stdio.h>

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    printf("%d\n", is_even(2));
    printf("%d\n", is_even(3));
    printf("%d\n", is_even(-4));
    return 0;
}