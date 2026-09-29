#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_power_of_two(unsigned int n) {
    return n && !(n & (n - 1));
}

bool is_woodall_number(unsigned int n) {
    for (unsigned int k = 1; k * k <= n; k++) {
        if (is_power_of_two(n + 1 + k)) {
            return true;
        }
    }
    return false;
}

int main() {
    unsigned int num;
    printf("Enter a number: ");
    if (scanf("%u", &num) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (is_woodall_number(num)) {
        printf("%u is a Woodall number.\n", num);
    } else {
        printf("%u is not a Woodall number.\n", num);
    }

    return 0;
}