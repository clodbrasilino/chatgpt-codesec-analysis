#include <stdio.h>
#include <stdbool.h>

bool opposite_signs(int a, int b) {
    return ((a ^ b) < 0);
}

int main(void) {
    int a, b;
    
    printf("Enter two integers: ");
    if (scanf("%d %d", &a, &b) != 2) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (opposite_signs(a, b)) {
        printf("Opposite signs\n");
    } else {
        printf("Same signs or zero\n");
    }
    
    return 0;
}