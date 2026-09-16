#include <stdio.h>
#include <stdbool.h>

bool is_valid_triangle(int a, int b, int c) {
    return (a + b > c) && (a + c > b) && (b + c > a);
}

int main() {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) == 3) {
        bool result = is_valid_triangle(a, b, c);
        if (result) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    } else {
        printf("Error: Invalid input\n");
    }
    return 0;
}