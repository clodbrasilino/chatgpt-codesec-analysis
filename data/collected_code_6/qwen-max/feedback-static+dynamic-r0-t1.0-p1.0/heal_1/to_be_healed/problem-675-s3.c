#include <stdio.h>

int add_with_condition(int a, int b, int low, int high) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1199547824 + 1073741824 cannot be represented in type 'int'
     */
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