#include <stdio.h>

int add_two_integers(int a, int b, int min_range, int max_range)
{
    int sum;
    
    if (min_range > max_range) {
        return -1;
    }
    
    sum = a + b;
    
    if (sum >= min_range && sum <= max_range) {
        return 20;
    }
    
    return sum;
}

int main(void)
{
    int result;
    
    result = add_two_integers(10, 15, 20, 30);
    printf("Result: %d\n", result);
    
    result = add_two_integers(5, 5, 20, 30);
    printf("Result: %d\n", result);
    
    return 0;
}