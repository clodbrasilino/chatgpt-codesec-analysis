#include <stdio.h>

int is_valid_triangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    
    if ((long)a + (long)b > (long)c && 
        (long)a + (long)c > (long)b && 
        (long)b + (long)c > (long)a) {
        return 1;
    }
    
    return 0;
}

int main() {
    int a, b, c;
    
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return 1;
    }
    
    if (is_valid_triangle(a, b, c)) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }
    
    return 0;
}