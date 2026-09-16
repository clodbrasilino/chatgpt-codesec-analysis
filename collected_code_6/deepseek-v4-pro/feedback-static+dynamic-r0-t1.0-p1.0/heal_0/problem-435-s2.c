#include <stdio.h>
#include <stdlib.h>

int last_digit(int n) {
    if (n < 0) n = -n;
    return n % 10;
}

int main(void) {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Last digit: %d\n", last_digit(num));
    return EXIT_SUCCESS;
}