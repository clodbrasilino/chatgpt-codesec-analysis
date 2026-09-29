#include <stdio.h>

long long newman_shanks_williams(int n) {
    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return 1;
    } else {
        long long prev_prev = 1;
        long long prev = 1;
        long long current;
        for (int i = 2; i <= n; i++) {
            current = 2 * prev + prev_prev;
            prev_prev = prev;
            prev = current;
        }
        return current;
    }
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The %dth Newman-Shanks-Williams prime number is %lld\n", n, newman_shanks_williams(n));
    return 0;
}