#include <stdio.h>

int jacobsthal(int n) {
    if (n <= 0)
        return -1;
    if (n == 1)
        return 0;
    if (n == 2)
        return 1;
    
    int a = 0, b = 1, result = 0;
    for (int i = 3; i <= n; i++) {
        result = 2 * b + a;
        a = b;
        b = result;
    }
    
    return result;
}

int main() {
    int n = 6;
    printf("The %dth Jacobsthal number is: %d\n", n, jacobsthal(n));
    
    return 0;
}