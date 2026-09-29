#include <stdio.h>
#include <stdlib.h>

int find_minimum(int a, int b);

int main(void) {
    int num1 = 0;
    int num2 = 0;
    int minimum_value = 0;

    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    minimum_value = find_minimum(num1, num2);
    
    printf("%d\n", minimum_value);

    return EXIT_SUCCESS;
}

int find_minimum(int a, int b) {
    return (a < b) ? a : b;
}