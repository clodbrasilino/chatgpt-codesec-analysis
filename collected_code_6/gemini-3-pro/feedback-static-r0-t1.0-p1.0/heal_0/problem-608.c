#include <stdio.h>
#include <stdlib.h>

unsigned long long find_nth_bell_number(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long **bell_triangle = (unsigned long long **)malloc((n + 1) * sizeof(unsigned long long *));
    if (bell_triangle == NULL) {
        return 0;
    }
    
    for (int i = 0; i <= n; i++) {
        bell_triangle[i] = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
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
    int n = 5;
    unsigned long long bell_number = find_nth_bell_number(n);
    if (bell_number != 0 || n == 0) {
        printf("%llu\n", bell_number);
    }
    return 0;
}