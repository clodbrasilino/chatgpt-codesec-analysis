#include <stdio.h>
#include <math.h>

long nextPerfectSquare(long n) {
    if(n < 0)
        return -1;
    long root = (long)sqrt(n);
    return (root + 1) * (root + 1);
}

int main() {
    long n;
    printf("Enter a number: ");
    scanf("%ld", &n);
    long result = nextPerfectSquare(n);
    if(result == -1)
        printf("Invalid input. Number must be non-negative\n");
    else
        printf("The next perfect square greater than %ld is %ld\n", n, result);
    return 0;
}