#include <stdio.h>

int find_maximum(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int main(void) {
    int num1 = 10;
    int num2 = 20;
    int max = find_maximum(num1, num2);
    
    printf("The maximum of %d and %d is %d\n", num1, num2, max);
    
    return 0;
}