#include <stdio.h>

int add_with_range(int a, int b, int min, int max) {
    int sum = a + b;
    if (sum >= min && sum <= max) {
        return 20;
    }
    return sum;
}

int main(void) {
    int result = add_with_range(5, 7, 10, 15);
    printf("%d\n", result);
    return 0;
}