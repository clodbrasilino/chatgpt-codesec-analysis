#include <stdio.h>
#include <stdbool.h>

bool is_even(int number) {
    return (number & 1) == 0;
}

int main(void) {
    int num = 4;
    if (is_even(num)) {
        printf("%d is even\n", num);
    } else {
        printf("%d is odd\n", num);
    }
    return 0;
}