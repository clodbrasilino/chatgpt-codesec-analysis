#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

double harmonic_sum(int n) {
    double sum = 0.0;
    double current = 1.0;
    int i;
    
    if (n <= 1) {
        return 0.0;
    }
    
    for (i = 1; i < n; i++) {
        sum += current / (double)i;
    }
    
    return sum;
}

int main(void) {
    char buffer[256];
    long val;
    int n;
    char *endptr;
    size_t len;
    int c;
    
    printf("Enter n: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    
    if (len == sizeof(buffer)) {
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    } else {
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || *endptr != '\0' || endptr == buffer) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (val > INT_MAX || val < 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    n = (int)val;
    
    if (n > 1000000) {
        fprintf(stderr, "Value too large\n");
        return 1;
    }
    
    printf("Harmonic sum of %d-1 = %.15f\n", n, harmonic_sum(n));
    
    return 0;
}