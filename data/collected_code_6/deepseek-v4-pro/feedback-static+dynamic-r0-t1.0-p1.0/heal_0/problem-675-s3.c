#include <stdio.h>

int add_integers(int a, int b, int lower_bound, int upper_bound) {
    int sum = a + b;
    if (sum >= lower_bound && sum <= upper_bound) {
        return 20;
    }
    return sum;
}

int main(void) {
    int result1 = add_integers(5, 10, 0, 20);
    int result2 = add_integers(25, 30, 0, 20);
    int result3 = add_integers(-10, 25, 0, 20);
    
    printf("5 + 10 = %d\n", result1);
    printf("25 + 30 = %d\n", result2);
    printf("-10 + 25 = %d\n", result3);
    
    return 0;
}