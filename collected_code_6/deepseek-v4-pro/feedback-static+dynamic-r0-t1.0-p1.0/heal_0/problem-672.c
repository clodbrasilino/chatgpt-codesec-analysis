#include <stdio.h>

int max_of_three(int a, int b, int c);

int max_of_three(int a, int b, int c) {
    int max = a;
    
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    
    return max;
}

int main(void) {
    int num1, num2, num3;
    
    printf("Enter three numbers: ");
    if (scanf("%d %d %d", &num1, &num2, &num3) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Maximum: %d\n", max_of_three(num1, num2, num3));
    
    return 0;
}