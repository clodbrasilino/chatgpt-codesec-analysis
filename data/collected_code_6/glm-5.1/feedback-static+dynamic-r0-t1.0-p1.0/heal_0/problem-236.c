#include <stdio.h>
#include <stdlib.h>

int count_equilateral_triangles(int n) {
    if (n <= 0) {
        return 0;
    }
    
    return (n * (n + 2) * (2 * n + 1)) / 8;
}

int main(int argc, char *argv[]) {
    int n;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <side_length>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    if (sscanf(argv[1], "%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Side length must be non-negative.\n");
        return EXIT_FAILURE;
    }
    
    int result = count_equilateral_triangles(n);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}