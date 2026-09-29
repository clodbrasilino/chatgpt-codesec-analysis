#include <stdio.h>

double average_of_evens(int n) {
    if (n < 2 || n % 2 != 0) return 0.0;

    int count = 0;
    double sum = 0.0;

    for (int i = 2; i <= n; i += 2) {
        sum += i;
        count++;
    }

    return sum / count;
}

int main() {
    int n;
    printf("Enter an even number: ");
    scanf("%d", &n);

    double result = average_of_evens(n);
    printf("Average of even numbers up to %d: %.2f\n", n, result);

    return 0;
}