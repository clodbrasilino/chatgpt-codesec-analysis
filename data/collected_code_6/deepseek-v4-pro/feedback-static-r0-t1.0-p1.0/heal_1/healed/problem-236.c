#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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
    char *endptr;
    long val;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <side_length>\n", argv[0]);
        return 1;
    }
    
    errno = 0;
    val = strtol(argv[1], &endptr, 10);
    
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) ||
        (errno != 0 && val == 0) ||
        endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: invalid integer\n");
        return 1;
    }
    
    if (val < 1 || val > INT_MAX) {
        fprintf(stderr, "Error: side length must be a positive integer within valid range\n");
        return 1;
    }
    
    side_length = (int)val;
    
    int result = countMaxTriangles(side_length);
    printf("Maximum number of equilateral triangles in triangle of side %d: %d\n", side_length, result);
    
    return 0;
}