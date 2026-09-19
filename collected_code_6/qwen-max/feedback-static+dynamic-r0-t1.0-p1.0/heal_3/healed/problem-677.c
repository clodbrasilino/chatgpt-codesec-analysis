#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_valid_triangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) return false;
    if (a > INT_MAX - b || b > INT_MAX - c || c > INT_MAX - a) return false;
    return (a + b > c) && (a + c > b) && (b + c > a);
}

int main() {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) == 3) {
        if (is_valid_triangle(a, b, c)) {
            printf("Valid triangle\n");
        } else {
            printf("Invalid triangle\n");
        }
    } else {
        printf("Error: Invalid input\n");
    }
    return 0;
}