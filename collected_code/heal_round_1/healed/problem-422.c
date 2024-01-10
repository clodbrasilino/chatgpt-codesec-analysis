#include <stdio.h>

double averageOfCubes(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i * i * i;
    }
    return (double) sum / n;
}

int main() {
    int n = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Error: n should be greater than 0\n");
        return 1;
    }
    
    double result = averageOfCubes(n);
    printf("The average of cubes of first %d natural numbers is: %.2lf\n", n, result);
    
    return 0;
}