#include <stdio.h>

int count_equal_numbers(int a, int b, int c) {
    if (a == b && b == c) {
        return 3;
    } else if (a == b || b == c || a == c) {
        return 2;
    } else {
        return 0;
    }
}

int main() {
    int a, b, c;
    printf("Enter three integers: ");
    scanf("%d %d %d", &a, &b, &c);
    printf("Number of equal numbers: %d\n", count_equal_numbers(a, b, c));
    return 0;
}