#include <stdio.h>

int carolNumber(int n) {
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result = result + (i * i + i);
    }
    return result;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("The %d'th Carol number is: %d\n", n, carolNumber(n));
    return 0;
}