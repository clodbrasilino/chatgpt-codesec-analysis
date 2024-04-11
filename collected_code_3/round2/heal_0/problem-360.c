#include <stdio.h>
#include <math.h>

long long int nthCarolNumber(int n) {
    return (long long int)pow(2, n) - 1 - pow(2, n - 1);
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth Carol number is %lld\n", n, nthCarolNumber(n));
    return 0;
}