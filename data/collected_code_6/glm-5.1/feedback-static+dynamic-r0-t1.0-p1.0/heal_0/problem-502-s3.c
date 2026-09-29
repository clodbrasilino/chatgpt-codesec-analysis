#include <stdio.h>
#include <stdlib.h>

int find_remainder(int dividend, int divisor) {
    if (divisor == 0) {
        exit(EXIT_FAILURE);
    }
    return dividend % divisor;
}

int main(void) {
    int a = 10;
    int b = 3;
    int result = find_remainder(a, b);
    printf("%d\n", result);
    return 0;
}