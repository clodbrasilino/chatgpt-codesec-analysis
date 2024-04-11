#include <stdio.h>
#include <math.h>

long nextPerfectSquare(long n) {
    long nextN = floor(sqrt(n)) + 1;
    return nextN * nextN;
}

int main() {
    long n;
    printf("Enter a number: ");
    scanf("%ld", &n);
    printf("Next perfect square is: %ld\n", nextPerfectSquare(n));
    return 0;
}