#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool have_opposite_signs(int a, int b) {
    if (a == 0 || b == 0) {
        return false;
    }
    
    if (a == INT_MIN && b == INT_MAX) {
        return true;
    }
    if (a == INT_MAX && b == INT_MIN) {
        return true;
    }
    
    return (a < 0) != (b < 0);
}

int main(void) {
    int num1, num2;
    
    printf("Enter two integers: ");
    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (have_opposite_signs(num1, num2)) {
        printf("The integers have opposite signs.\n");
    } else {
        printf("The integers do not have opposite signs.\n");
    }
    
    return 0;
}