#include <stdio.h>
#include <limits.h>

int find_closest_smaller(int n) {
    if (n == INT_MIN) {
        return INT_MIN;
    }
    return --n;
}

int main() {
    int n = 10;
    int result = find_closest_smaller(n);
    printf("The closest smaller number than %d is %d\n", n, result);
    return 0;
}