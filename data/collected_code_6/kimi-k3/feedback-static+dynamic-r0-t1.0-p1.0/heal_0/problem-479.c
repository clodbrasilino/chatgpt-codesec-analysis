#include <stdio.h>
#include <stdlib.h>

int first_digit(int number) {
    int n = abs(number);
    while (n >= 10) {
        n /= 10;
    }
    return n;
}

int main(void) {
    int number;
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("%d\n", first_digit(number));
    return 0;
}