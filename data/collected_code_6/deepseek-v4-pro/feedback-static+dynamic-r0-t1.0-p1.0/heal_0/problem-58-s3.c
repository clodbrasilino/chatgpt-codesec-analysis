#include <stdio.h>

int have_opposite_signs(int a, int b) {
    return ((a ^ b) < 0);
}

int main(void) {
    int a, b;
    
    printf("Enter two integers: ");
    if (scanf("%d %d", &a, &b) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (have_opposite_signs(a, b)) {
        printf("The integers have opposite signs.\n");
    } else {
        printf("The integers have the same sign.\n");
    }
    
    return 0;
}