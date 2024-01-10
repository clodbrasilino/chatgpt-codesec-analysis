#include <stdio.h>

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
    int n = 0;
    printf("Enter the value of n: ");
    if(scanf("%d", &n) != 1){
        printf("Invalid Input\n");
        return -1;
    }

    printf("Sum of Perrin numbers up to %d is %d\n", n, perrinSum(n));

    return 0;
}