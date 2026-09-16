#include <stdio.h>
#include <stdlib.h>

int is_isosceles(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return 0;
    }
    if (a == b || b == c || a == c) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }
    
    long va = strtol(argv[1], NULL, 10);
    long vb = strtol(argv[2], NULL, 10);
    long vc = strtol(argv[3], NULL, 10);
    
    if (va <= 0 || vb <= 0 || vc <= 0) {
        return EXIT_FAILURE;
    }
    
    int a = (int)va;
    int b = (int)vb;
    int c = (int)vc;
    
    if (is_isosceles(a, b, c)) {
        printf("Isosceles\n");
    } else {
        printf("Not Isosceles\n");
    }
    
    return EXIT_SUCCESS;
}