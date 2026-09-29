#include <stdio.h>
#include <stdlib.h>

int find_first_digit(int num) {
    if (num == 0) {
        return 0;
    }
    int n = abs(num);
    while (n >= 10) {
        n /= 10;
    }
    return n;
}

int main() {
    int value;
    if (scanf("%d", &value) != 1) {
        return EXIT_FAILURE;
    }
    int result = find_first_digit(value);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}