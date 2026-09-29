#include <stdio.h>

int multiply(int a, int b) {
    int result = 0;
    for(int i = 0; i < b; i++) {
        result += a;
    }
    return result;
}

int main() {
    int a = 5;
    int b = 4;
    printf("Product of %d and %d is %d\n", a, b, multiply(a, b));
    return 0;
}