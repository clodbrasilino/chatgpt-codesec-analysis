#include <stdio.h>
#include <stdlib.h>

int find_parity(int number) {
    return (number & 1) ? 1 : 0;
}

int main(void) {
    int number;
    int parity;

    printf("Enter an integer: ");
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    parity = find_parity(number);
    printf("Parity: %s\n", parity ? "Odd" : "Even");

    return EXIT_SUCCESS;
}