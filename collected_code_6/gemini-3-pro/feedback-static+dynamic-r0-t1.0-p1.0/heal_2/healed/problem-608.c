#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

unsigned long long find_nth_bell_number(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long **bell_triangle = malloc((n + 1) * sizeof(unsigned long long *));
    if (bell_triangle == NULL) {
        return 0;
    }
    
    for (int i = 0; i <= n; i++) {
        bell_triangle[i] = malloc((n + 1) * sizeof(unsigned long long));
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

int main(int argc, const char *argv[]) {
    int n = 5;
    
    if (argc > 1) {
        char *endptr;
        errno = 0;
        long parsed_value = strtol(argv[1], &endptr, 10);
        
        if (errno == ERANGE || parsed_value < 0 || parsed_value > 26 || endptr == argv[1] || *endptr != '\0') {
            return 1;
        }
        
        n = (int)parsed_value;
    }
    
    unsigned long long bell_number = find_nth_bell_number(n);
    
    if (bell_number != 0) {
        printf("%llu\n", bell_number);
    }
    
    return 0;
}