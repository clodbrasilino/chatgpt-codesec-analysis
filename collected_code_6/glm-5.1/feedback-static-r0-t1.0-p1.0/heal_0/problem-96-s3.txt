#include <stdio.h>

int count_divisors(int n) {
    if (n <= 0) {
        return 0;
    }
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int num = 28;
    int result = count_divisors(num);
    printf("%d\n", result);
    return 0;
}