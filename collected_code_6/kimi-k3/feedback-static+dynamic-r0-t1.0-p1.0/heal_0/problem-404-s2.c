#include <stdio.h>

int min(int a, int b);

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main(void) {
    int num1, num2;
    
    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("%d\n", min(num1, num2));
    
    return 0;
}