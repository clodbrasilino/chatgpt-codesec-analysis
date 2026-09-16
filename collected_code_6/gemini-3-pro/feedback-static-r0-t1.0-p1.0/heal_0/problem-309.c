#include <stdio.h>
#include <stdlib.h>

int find_max(int a, int b);

int find_max(int a, int b) {
    return (a > b) ? a : b;
}

int main(void) {
    int num1 = 0;
    int num2 = 0;

    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int max_val = find_max(num1, num2);
    
    if (printf("%d\n", max_val) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}