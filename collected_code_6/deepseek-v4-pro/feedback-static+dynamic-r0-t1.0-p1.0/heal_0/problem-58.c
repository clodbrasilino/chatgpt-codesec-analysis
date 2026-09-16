#include <stdio.h>
#include <stdbool.h>

bool opposite_signs(int a, int b) {
    return ((a ^ b) < 0);
}

int main(void) {
    int x, y;
    
    printf("Enter two integers: ");
    if (scanf("%d %d", &x, &y) != 2) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (opposite_signs(x, y)) {
        printf("%d and %d have opposite signs\n", x, y);
    } else {
        printf("%d and %d have same sign\n", x, y);
    }
    
    return 0;
}