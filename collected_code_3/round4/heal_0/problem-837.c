#include <stdio.h>

int cubeSum(int n) {
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        int odd = 2 * i - 1;
        sum += odd * odd * odd;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Cube sum of first %d odd natural numbers is %d\n", n, cubeSum(n));
    return 0;
}