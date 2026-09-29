#include <stdio.h>

int add_with_range_check(int a, int b, int lower, int upper) {
    int sum = a + b;
    if (sum >= lower && sum <= upper) {
        return 20;
    }
    return sum;
}

int main(void) {
    int num1 = 5;
    int num2 = 7;
    int lower_bound = 10;
    int upper_bound = 20;
    
    int result = add_with_range_check(num1, num2, lower_bound, upper_bound);
    printf("%d\n", result);
    
    return 0;
}