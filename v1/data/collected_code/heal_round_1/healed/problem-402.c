#include <stdio.h>

int factorial(int num) {
    int fact = 1;
    for (int i = 1; i <= num; ++i) {
        fact *= i;
    }
    return fact;
}

int nCr_mod_p(int n, int r, int p) {
    int nCr = factorial(n) / (factorial(r) * factorial(n - r));
    return nCr % p;
}

int main() {
    int n = 0;
    int r = 0;
    int p = 0;
    
    printf("Enter the values of n, r, and p: ");
    scanf("%d %d %d", &n, &r, &p);
    
    int result = nCr_mod_p(n, r, p);
    
    printf("nCr %% p = %d", result);

    return 0;
}