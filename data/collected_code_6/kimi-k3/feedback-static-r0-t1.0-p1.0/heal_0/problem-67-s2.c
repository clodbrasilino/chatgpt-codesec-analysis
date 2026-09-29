#include <stdio.h>
#include <stdlib.h>

unsigned long long bell_number(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long **bell_triangle = (unsigned long long **)malloc((size_t)(n + 1) * sizeof(unsigned long long *));
    if (bell_triangle == NULL) {
        return 0;
    }
    
    for (int i = 0; i <= n; i++) {
        bell_triangle[i] = (unsigned long long *)malloc((size_t)(n + 1) * sizeof(unsigned long long));
        if (bell_triangle[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(bell_triangle[j]);
            }
            free(bell_triangle);
            return 0;
        }
    }
    
    bell_triangle[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        bell_triangle[i][0] = bell_triangle[i - 1][i - 1];
        for (int j = 1; j <= i; j++) {
            bell_triangle[i][j] = bell_triangle[i - 1][j - 1] + bell_triangle[i][j - 1];
        }
    }
    
    unsigned long long result = bell_triangle[n][0];
    
    for (int i = 0; i <= n; i++) {
        free(bell_triangle[i]);
    }
    free(bell_triangle);
    
    return result;
}

int main(void) {
    int n;
    
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 0) {
        fprintf(stderr, "Number must be non-negative\n");
        return 1;
    }
    
    unsigned long long result = bell_number(n);
    printf("Bell number B(%d) = %llu\n", n, result);
    
    return 0;
}