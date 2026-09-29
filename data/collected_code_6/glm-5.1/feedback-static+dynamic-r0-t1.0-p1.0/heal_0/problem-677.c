#include <stdio.h>
#include <stdlib.h>

int is_valid_triangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if ((unsigned int)a + (unsigned int)b <= (unsigned int)c) {
        return 0;
    }
    if ((unsigned int)a + (unsigned int)c <= (unsigned int)b) {
        return 0;
    }
    if ((unsigned int)b + (unsigned int)c <= (unsigned int)a) {
        return 0;
    }
    return 1;
}

int main(void) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (is_valid_triangle(a, b, c)) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }
    return EXIT_SUCCESS;
}