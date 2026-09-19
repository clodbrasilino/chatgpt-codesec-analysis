#include <stdio.h>
#include <stdlib.h>

int countMaxTriangles(int n) {
    if (n < 1) {
        return 0;
    }
    
    int total = 0;
    for (int i = 1; i <= n; i++) {
        total += i * (n - i + 1);
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) {
            total += (n - i - j + 1);
        }
    }
    
    return total;
}

int main(int argc, const char *argv[]) {
    int side_length = 0;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <side_length>\n", argv[0]);
        return 1;
    }
    
    side_length = atoi(argv[1]);
    
    if (side_length < 1) {
        fprintf(stderr, "Error: side length must be a positive integer\n");
        return 1;
    }
    
    int result = countMaxTriangles(side_length);
    printf("Maximum number of equilateral triangles in triangle of side %d: %d\n", side_length, result);
    
    return 0;
}