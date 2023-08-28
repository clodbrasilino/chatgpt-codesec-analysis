#include <stdio.h>

double averageOfCubes(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i * i * i;
    }
    return (double) sum / n;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    
    double result = averageOfCubes(n);
    printf("The average of cubes of first %d natural numbers is: %.2lf\n", n, result);
    
    return 0;
}