#include <stdio.h>
#include <stdlib.h>

int swap_numbers(int *a, int *b);

int swap_numbers(int *a, int *b) {
    if (a == NULL || b == NULL) {
        return -1;
    }

    int temp = *a;
    *a = *b;
    *b = temp;

    return 0;
}

int main(void) {
    int value1 = 15;
    int value2 = 42;

    if (swap_numbers(&value1, &value2) != 0) {
        return EXIT_FAILURE;
    }

    printf("%d %d\n", value1, value2);

    return EXIT_SUCCESS;
}