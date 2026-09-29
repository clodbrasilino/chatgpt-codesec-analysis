#include <stdio.h>
#include <math.h>

int is_even_divisor_count(int n) {
    if (n <= 0) {
        return -1;
    }
    
    int root = (int)sqrt(n);
    
    if (root * root == n) {
        return 0;
    }
    return 1;
}

int main(void) {
    printf("%d\n", is_even_divisor_count(4));
    printf("%d\n", is_even_divisor_count(6));
    printf("%d\n", is_even_divisor_count(16));
    printf("%d\n", is_even_divisor_count(12));
    printf("%d\n", is_even_divisor_count(0));
    
    return 0;
}