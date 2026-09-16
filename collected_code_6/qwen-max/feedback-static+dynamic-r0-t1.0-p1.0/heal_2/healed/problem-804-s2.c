#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

bool isProductEven(int n, ...) {
    va_list args;
    va_start(args, n);
    for (int i = 0; i < n; ++i) {
        int num = va_arg(args, int);
        if (num % 2 == 0) {
            va_end(args);
            return true;
        }
    }
    va_end(args);
    return false;
}

int main() {
    if (isProductEven(3, 2, 3, 5)) {
        printf("Product is even\n");
    } else {
        printf("Product is odd\n");
    }

    if (isProductEven(3, 1, 3, 5)) {
        printf("Product is even\n");
    } else {
        printf("Product is odd\n");
    }

    return 0;
}