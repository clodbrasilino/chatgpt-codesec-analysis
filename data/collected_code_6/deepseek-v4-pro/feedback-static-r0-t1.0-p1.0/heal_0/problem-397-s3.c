#include <stdio.h>

int median_of_three(int a, int b, int c) {
    if ((a >= b && a <= c) || (a <= b && a >= c)) {
        return a;
    }
    if ((b >= a && b <= c) || (b <= a && b >= c)) {
        return b;
    }
    return c;
}

int main(void) {
    int a = 10, b = 20, c = 15;
    printf("Median of %d, %d, %d is %d\n", a, b, c, median_of_three(a, b, c));
    
    a = 5; b = 5; c = 1;
    printf("Median of %d, %d, %d is %d\n", a, b, c, median_of_three(a, b, c));
    
    a = -3; b = -7; c = -5;
    printf("Median of %d, %d, %d is %d\n", a, b, c, median_of_three(a, b, c));
    
    return 0;
}