#include <stdio.h>

int sum_series(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n;
        n -= 2;
    }
    return sum;
}

int main() {
    int n = 10;
    int result = sum_series(n);
    printf("The sum of the series is: %d\n", result);
    return 0;
}