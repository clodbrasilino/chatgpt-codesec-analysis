#include <stdio.h>
#include <stdlib.h>

int find_common_divisor(int a, int b) {
    int temp_a = abs(a);
    int temp_b = abs(b);
    
    while (temp_b != 0) {
        int remainder = temp_a % temp_b;
        temp_a = temp_b;
        temp_b = remainder;
    }
    
    return temp_a;
}

int main(void) {
    int num1, num2;
    
    if (scanf("%d %d", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }
    
    if (num1 == 0 && num2 == 0) {
        return EXIT_FAILURE;
    }
    
    int result = find_common_divisor(num1, num2);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}