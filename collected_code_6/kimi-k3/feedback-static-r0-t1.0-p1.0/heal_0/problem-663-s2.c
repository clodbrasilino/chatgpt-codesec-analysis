#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#define MAX_K 1000000

int find_largest_k(int x, int y) {
    if (x <= 0 || y < 0 || y >= x) {
        return -1;
    }
    
    int k = MAX_K - (MAX_K % x) + y;
    
    if (k > MAX_K) {
        k -= x;
    }
    
    return k;
}

int main(void) {
    int x, y;
    
    printf("Enter x and y: ");
    
    if (scanf("%d %d", &x, &y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    int result = find_largest_k(x, y);
    
    if (result == -1) {
        printf("No valid k exists\n");
    } else {
        printf("Largest k: %d\n", result);
    }
    
    return 0;
}