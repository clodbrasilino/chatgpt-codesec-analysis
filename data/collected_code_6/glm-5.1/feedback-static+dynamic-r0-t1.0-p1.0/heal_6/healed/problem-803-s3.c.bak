#include <stdio.h>
#include <math.h>

int is_perfect_square(long long num) {
    if (num < 0) {
        return 0;
    }
    if (num == 0) {
        return 1;
    }
    long long root = (long long)sqrt((double)num);
    while (root > 0 && root * root > num) {
        root--;
    }
    while (root != 0 && num / root > root) {
        root++;
    }
    return root > 0 && root * root == num;
}

int main(void) {
    long long val;
    if (scanf("%lld", &val) == 1) {
        if (is_perfect_square(val)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }
    return 0;
}