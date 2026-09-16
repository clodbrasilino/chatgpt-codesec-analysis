#include <stdio.h>
#include <stdbool.h>

bool is_valid_triangle(int a, int b, int c) {
    return (a > 0 && b > 0 && c > 0 && 
            a + b > c && b + c > a && a + c > b);
}

bool is_scalene(int a, int b, int c) {
    if (!is_valid_triangle(a, b, c)) {
        return false;
    }
    return (a != b && b != c && a != c);
}

int main(void) {
    int a, b, c;
    
    printf("Enter three sides of the triangle: ");
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (!is_valid_triangle(a, b, c)) {
        printf("Not a valid triangle\n");
        return 0;
    }
    
    if (is_scalene(a, b, c)) {
        printf("The triangle is scalene\n");
    } else {
        printf("The triangle is not scalene\n");
    }
    
    return 0;
}