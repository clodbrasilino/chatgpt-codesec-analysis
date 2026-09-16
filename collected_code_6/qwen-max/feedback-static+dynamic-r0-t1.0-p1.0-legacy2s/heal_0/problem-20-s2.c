#include <stdio.h>
#include <math.h>

int is_power_of_two(int n) {
    return (n > 0) && !(n & (n - 1));
}

int is_woodall_number(int n) {
    int i;
    for (i = 1; ; i++) {
        if (pow(2, i) * i - 1 > n) {
            break;
        }
        if (pow(2, i) * i - 1 == n) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int num = 31;
    if (is_woodall_number(num)) {
        printf("%d is a Woodall number.\n", num);
    } else {
        printf("%d is not a Woodall number.\n", num);
    }
    return 0;
}