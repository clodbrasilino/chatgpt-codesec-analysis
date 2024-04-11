#include <stdio.h>

long long demloNumber(int n) {
    long long demlo = 1;
    for(int i = 0; i < n; i++) {
        demlo = (demlo * 10 + 1) % 1000000007;
    }
    return (demlo * demlo) % 1000000007;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Demlo number for %d is %lld\n", n, demloNumber(n));
    return 0;
}