#include <stdio.h>
#include <stdbool.h>

bool is_scalene(int a, int b, int c) {
    return a + b > c && a + c > b && b + c > a && a != b && b != c && a != c;
}

int main() {
    int side1 = 5, side2 = 7, side3 = 10;
    bool result = is_scalene(side1, side2, side3);
    if (result) {
        printf("The triangle is scalene.\n");
    } else {
        printf("The triangle is not scalene.\n");
    }
    return 0;
}