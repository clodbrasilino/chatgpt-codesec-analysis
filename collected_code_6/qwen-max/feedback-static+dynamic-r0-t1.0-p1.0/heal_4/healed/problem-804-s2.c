#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

bool isProductEven(int n, ...) {
    va_list args;
    bool result = true;
    va_start(args, n);
    for (int i = 0; i < n; ++i) {
        int num = va_arg(args, int);
        if (num % 2 != 0) {
            result = false;
            break;
        }
    }
    va_end(args);
    return !result;
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

    if (isProductEven(3, 2, 4, 6)) {
        printf("Product is even\n");
    } else {
        printf("Product is odd\n");
    }

    return 0;
}