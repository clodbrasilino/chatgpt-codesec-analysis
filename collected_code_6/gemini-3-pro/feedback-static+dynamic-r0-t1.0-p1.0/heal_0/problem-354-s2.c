#include <stdio.h>
#include <stdlib.h>

int find_nth_term(int a, int d, int n) {
    if (n <= 0) {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        exit(EXIT_FAILURE);
    }
    return a + (n - 1) * d;
}

int main(void) {
    int a = 1; 
    int d = 2; 
    int n = 5; 
    
    int result = find_nth_term(a, d, n);
    
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}