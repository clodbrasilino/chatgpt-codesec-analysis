#include <stdio.h>
#include <stdlib.h>

int count_equal(int a, int b, int c) {
    if (a == b && b == c) {
        return 3;
    } else if (a == b || b == c || a == c) {
        return 2;
    } else {
        return 0;
    }
}

int main(void) {
    int num1 = 5;
    int num2 = 5;
    int num3 = 8;
    
    int result = count_equal(num1, num2, num3);
    
    printf("Number of equal numbers: %d\n", result);
    
    return EXIT_SUCCESS;
}