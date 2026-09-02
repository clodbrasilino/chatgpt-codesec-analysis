#include <stdio.h>
#include <stdlib.h>

int sum_first_even_and_odd(const int *list, int size) {
    int first_even = 0;
    int first_odd = 0;
    int even_found = 0;
    int odd_found = 0;

    for (int i = 0; i < size; i++) {
        if (!even_found && list[i] % 2 == 0) {
            first_even = list[i];
            even_found = 1;
        }
        if (!odd_found && list[i] % 2 != 0) {
            first_odd = list[i];
            odd_found = 1;
        }
        if (even_found && odd_found) {
            break;
        }
    }

    if (!even_found || !odd_found) {
        fprintf(stderr, "Error: List must contain at least one even and one odd number\n");
        exit(EXIT_FAILURE);
    }

    return first_even + first_odd;
}

int main(void) {
    int list[] = {3, 5, 2, 8, 7, 10, 12};
    int size = sizeof(list) / sizeof(list[0]);
    int result = sum_first_even_and_odd(list, size);
    printf("%d\n", result);

    return 0;
}