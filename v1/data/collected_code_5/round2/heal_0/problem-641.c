#include <stdio.h>

long long nonagonalNumber(int n) {
    return n * ((7 * n) - 5) / 2;
}

int main() {
    int n;
    scanf("%d", &n);
    
    if(n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
  
    printf("%lld\n", nonagonalNumber(n));
  
    return 0;
}