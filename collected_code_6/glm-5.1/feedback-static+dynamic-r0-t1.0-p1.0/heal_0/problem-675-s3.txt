#include <stdio.h>
#include <limits.h>

int add_and_check(int a, int b, int lower, int upper) {
    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
        return 0;
    }
    int sum = a + b;
    if (sum >= lower && sum <= upper) {
        return 20;
    }
    return sum;
}

int main() {
    int result1 = add_and_check(5, 10, 10, 20);
    printf("%d\n", result1);
    int result2 = add_and_check(5, 10, 0, 5);
    printf("%d\n", result2);
    int result3 = add_and_check(INT_MAX, 1, 0, 100);
    printf("%d\n", result3);
    return 0;
}