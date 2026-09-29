#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_valid_triangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return false;
    }
    
    if (a > INT_MAX - b || a > INT_MAX - c ||
        b > INT_MAX - a || b > INT_MAX - c ||
        c > INT_MAX - a || c > INT_MAX - b) {
        if ((long long)a + b > c && (long long)b + c > a && (long long)a + c > b) {
            return true;
        }
        return false;
    }
    
    if (a + b <= c || b + c <= a || a + c <= b) {
        return false;
    }
    
    return true;
}

int main(void) {
    int a, b, c;
    
    printf("Enter three sides of a triangle: ");
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (is_valid_triangle(a, b, c)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }
    
    return 0;
}