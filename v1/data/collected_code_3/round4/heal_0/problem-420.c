#include <stdio.h>

long long cubeSum(int n) {
    long long sum = 0;
    long long cube;
    for(int i = 1; i <= n; i++) {
        cube = 2 * i;
        sum += cube * cube * cube;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Cube sum of first %d even natural numbers is %lld\n", n, cubeSum(n));
    return 0;
}