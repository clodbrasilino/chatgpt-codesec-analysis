#include <stdio.h>

int find_max(int a, int b) {
    return a > b ? a : b;
}

int main(void) {
    int x = 0;
    int y = 0;
    
    if (scanf("%d %d", &x, &y) == 2) {
        printf("%d\n", find_max(x, y));
        return 0;
    }
    
    return 1;
}