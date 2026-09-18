#include <stdio.h>
#include <stdlib.h>

double geometricSum(int n) {
    if(n < 0) {
        printf("Error: Negative numbers are not allowed.\n");
        exit(EXIT_FAILURE);
    }

    double sum = 0.0;
    for(int i = 0; i < n; i++) {
        sum += 1.0 / (1 << i);
    }

    return sum;
}

int main() {
    int n;
    
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    double sum = geometricSum(n);

    printf("Geometric Sum till %d is %lf\n", n, sum);

    return 0;
}