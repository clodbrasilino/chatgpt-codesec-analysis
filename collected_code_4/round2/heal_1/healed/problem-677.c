#include <stdio.h>
#include <stdbool.h>

bool isValidTriangle(int a, int b, int c) {
    if ((a + b > c) && (a + c > b) && (b + c > a)) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int a = 7, b = 10, c = 5;

    if (isValidTriangle(a, b, c)) {
        printf("Valid Triangle\n");
    } else {
        printf("Invalid Triangle\n");
    }

    return 0;
}