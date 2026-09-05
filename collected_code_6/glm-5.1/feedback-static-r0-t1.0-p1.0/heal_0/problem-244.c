#include <stdio.h>
#include <math.h>

unsigned long long find_next_perfect_square(long long num) {
    if (num < 0) {
        return 0;
    }
    unsigned long long target = (unsigned long long)num + 1;
    unsigned long long root = (unsigned long long)ceil(sqrt((double)target));
    return root * root;
}

int main(void) {
    long long input;
    if (scanf("%lld", &input) != 1) {
        return 1;
    }
    unsigned long long result = find_next_perfect_square(input);
    printf("%llu\n", result);
    return 0;
}