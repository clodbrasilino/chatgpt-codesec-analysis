#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_woodall(int n) {
    if (n < 1) {
        return false;
    }

    int i = 1;
    while (true) {
        long long woodall = (long long)i * (1LL << i) - 1;
        if (woodall == n) {
            return true;
        }
        if (woodall > n) {
            return false;
        }
        i++;
    }
}

int main(void) {
    int num;

    if (scanf("%d", &num) != 1) {
        return EXIT_FAILURE;
    }

    if (is_woodall(num)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}