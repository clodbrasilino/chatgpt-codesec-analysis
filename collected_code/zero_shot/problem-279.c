#include <stdio.h>

int decagonalNumber(int n) {
    return 3 * n * (n - 1) + 1;
}

int main() {
    int n = 5;
    int decagonal = decagonalNumber(n);
    printf("The %dth decagonal number is %d.\n", n, decagonal);
    
    return 0;
}