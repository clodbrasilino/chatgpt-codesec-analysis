#include <stdio.h>

int add(int num1, int num2, int lower, int upper) {
    int sum = num1 + num2;
    if (sum > lower && sum < upper) {
        return 20;
    }
    return sum;
}

int main() {
    int num1 = 5, num2 = 10, lower = 10, upper = 20;
    int result = add(num1, num2, lower, upper);
    printf("Result: %d\n", result);
    return 0;
}