#include <stdio.h>

int sum_series(int n) {
    if (n <= 0) {
        return 0;
    }
    return n + sum_series(n - 2);
}

int main() {
    int n = 10;  // Example input
    int result = sum_series(n);
    printf("%d\n", result);
    return 0;
}