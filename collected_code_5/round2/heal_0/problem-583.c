#include <stdio.h>

unsigned long int binomialCoeff(unsigned int n, unsigned int k) {
    unsigned long int res = 1;
  
    if (k > n - k)
        k = n - k;
  
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
  
    return res;
}
  
unsigned long int catalan(unsigned int n) {
    unsigned long int c = binomialCoeff(2*n, n);
  
    return c/(n + 1);
}

int main() {
    unsigned int n;
    printf("Enter a positive integer: ");
    scanf("%u",&n);
  
    if(n >=0) {
        printf("The %uth Catalan number is %lu\n", n, catalan(n));
    } else {
        printf("Please enter a non-negative integer.\n");
    }
  
    return 0;
}