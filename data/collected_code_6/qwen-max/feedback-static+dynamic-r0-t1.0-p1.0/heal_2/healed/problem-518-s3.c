#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

bool is_perfect_square(int n) {
    if (n < 0) return false;
    int64_t root = (int64_t)sqrt(n);
    return (int64_t)n == root * root;
}

int main() {
    int num;

    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        return 1;
    }

    if (is_perfect_square(num)) {
        int64_t root = (int64_t)sqrt(num);
        printf("The square root of %d is %lld\n", num, root);
    } else {
        printf("%d is not a perfect square\n", num);
    }

    return 0;
}