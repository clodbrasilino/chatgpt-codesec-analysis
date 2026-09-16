#include <stdio.h>
#include <limits.h>

int add_with_condition(int a, int b, int low, int high) {
    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
        return 20;
    }
    int sum = a + b;
    if (sum > low && sum < high) {
        return 20;
    }
    return sum;
}

int main() {
    int a, b, low, high;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    printf("Enter the range (low high): ");
    scanf("%d %d", &low, &high);

    int result = add_with_condition(a, b, low, high);
    printf("Result: %d\n", result);

    return 0;
}