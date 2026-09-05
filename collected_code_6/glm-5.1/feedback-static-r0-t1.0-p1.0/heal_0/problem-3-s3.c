#include <stdio.h>
#include <stdbool.h>

bool is_non_prime(int num) {
    if (num <= 1) {
        return true;
    }
    if (num == 2) {
        return false;
    }
    if (num % 2 == 0) {
        return true;
    }
    for (int i = 3; i * i <= num; i += 2) {
        if (num % i == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    int val;
    while (scanf("%d", &val) == 1) {
        if (is_non_prime(val)) {
            printf("%d\n", val);
        }
    }
    if (ferror(stdin)) {
        return 1;
    }
    return 0;
}