#include <stdio.h>
#include <stdlib.h>

int min_operations(int a, int b) {
    int diff = abs(a - b);
    return (diff * 2 + 1) / 3; 
}

int main(void) {
    int a, b;
    
    if (scanf("%d %d", &a, &b) == 2) {
        int result = min_operations(a, b);
        printf("%d\n", result);
    }
    
    return EXIT_SUCCESS;
}