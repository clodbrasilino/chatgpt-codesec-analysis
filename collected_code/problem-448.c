#include <stdio.h>

// Function to calculate the sum of Perrin numbers
int perrinSum(int n) {
    int a = 3, b = 0, c = 2, sum = 0;

    if (n == 0)
        return a;

    sum += a + b + c;
    for (int i = 3; i <= n; i++) {
        int next = a + b;
        sum += next;

        a = b;
        b = c;
        c = next;
    }

    return sum;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("Sum of Perrin numbers up to %d is %d\n", n, perrinSum(n));

    return 0;
}