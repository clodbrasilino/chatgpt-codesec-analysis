#include <stdio.h>

int add_numbers(int a, int b, int min, int max) {
    int sum = a + b;
    if (sum > min && sum < max) {
        return 20;
    }
    return sum;
}

int main() {
    int a = 5, b = 15, min = 10, max = 30;
    int result = add_numbers(a, b, min, max);
    printf("Result: %d\n", result);
    return 0;
}