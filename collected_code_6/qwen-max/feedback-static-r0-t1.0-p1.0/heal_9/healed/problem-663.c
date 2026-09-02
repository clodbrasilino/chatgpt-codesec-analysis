#include <stdio.h>
#include <stdlib.h>

int find_largest_k(int x, int y) {
    if (x <= 0 || y < 0 || y >= x) {
        return -1;
    }
    return (x + y - 1) % x;
}

int main() {
    int x = 7;
    int y = 3;
    int result = find_largest_k(x, y);
    
    if (result == -1) {
        printf("Invalid input or no solution\n");
    } else {
        printf("The largest k is: %d\n", result);
    }
    return 0;
}