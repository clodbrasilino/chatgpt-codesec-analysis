#include <stdio.h>
#include <stdlib.h>

int multiply(int a, int b) {
    int result = 0;
    for(int i = 0; i < abs(b); i++) {
        result += a;
    }
    return b < 0 ? -result : result;
}

int main() {
    int a = 5;
    int b = 4;
    printf("The product of %d and %d is %d\n", a, b, multiply(a, b));
    return 0;
}