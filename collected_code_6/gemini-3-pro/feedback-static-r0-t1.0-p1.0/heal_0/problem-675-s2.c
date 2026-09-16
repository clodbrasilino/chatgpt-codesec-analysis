#include <stdio.h>
#include <limits.h>

int add_with_range(int a, int b, int min, int max);

int main(void) {
    int a = 10;
    int b = 5;
    int min_range = 10;
    int max_range = 19;
    int result = 0;

    result = add_with_range(a, b, min_range, max_range);
    printf("%d\n", result);

    a = 2;
    b = 3;
    result = add_with_range(a, b, min_range, max_range);
    printf("%d\n", result);

    return 0;
}

int add_with_range(int a, int b, int min, int max) {
    long long sum = (long long)a + (long long)b;

    if (sum >= (long long)min && sum <= (long long)max) {
        return 20;
    }

    if (sum > INT_MAX || sum < INT_MIN) {
        return 0; 
    }

    return (int)sum;
}