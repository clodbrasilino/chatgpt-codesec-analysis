#include <stdio.h>

float harmonicSum(int n) {
    float sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

int main() {
    int n = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    if(n <= 0) {
        printf("Please enter valid input greater than 0.\n");
        return 1;
    }

    float result = harmonicSum(n);
    printf("Harmonic Sum of %d: %.2f\n", n, result);

    return 0;
}