#include <stdio.h>

int add(int a, int b, int min, int max) {
    int sum = a + b;
    if (sum > min && sum < max) {
        return 20;
    }
    return sum;
}

int main() {
    int a = 5, b = 10, min = 10, max = 20;
    printf("%d\n", add(a, b, min, max));
    return 0;
}