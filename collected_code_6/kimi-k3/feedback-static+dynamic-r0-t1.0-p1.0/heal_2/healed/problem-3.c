#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    int num;
    if (scanf("%d", &num) != 1) {
        return 1;
    }
    if (is_prime(num)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    return 0;
}