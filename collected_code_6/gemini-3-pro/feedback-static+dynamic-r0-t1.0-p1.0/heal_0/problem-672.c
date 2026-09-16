#include <stdio.h>
#include <stdlib.h>

int find_max(int a, int b, int c);

int main(void) {
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int max = 0;

    if (scanf("%d %d %d", &num1, &num2, &num3) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    max = find_max(num1, num2, num3);
    
    printf("%d\n", max);

    return EXIT_SUCCESS;
}

int find_max(int a, int b, int c) {
    int max = a;

    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }

    return max;
}