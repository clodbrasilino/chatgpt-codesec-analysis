#include <stdio.h>
#include <math.h>

long long demloNumber(int n) {
    long long demlo = 0;
    for (int i = 0; i < n; i++) {
        demlo = demlo * 10 + 1;
    }
    return demlo * demlo;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Demlo number for %d is %lld\n", n, demloNumber(n));
    return 0;
}