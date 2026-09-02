#include <stdio.h>
#include <math.h>

int find_smallest_power_of_2(int n) {
    if (n <= 0) return 1;
    int exponent = ceil(log2(n));
    return 1 << exponent;
}

int main() {
    int n;
    scanf("%d", &n);
    int result = find_smallest_power_of_2(n);
    printf("%d\n", result);
    return 0;
}