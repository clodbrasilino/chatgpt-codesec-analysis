#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t sum_series(int64_t n) {
    if (n <= 0) {
        return 0;
    }
    if (n % 2 == 0) {
        return (n / 2) * (n + 1);
    } else {
        return n * ((n + 1) / 2);
    }
}

int64_t sum_triangular(int64_t n) {
    if (n <= 0) {
        return 0;
    }
    
    int64_t a = n;
    int64_t b = n + 1;
    int64_t c = n + 2;
    
    if (a % 3 == 0) {
        a /= 3;
    } else if (b % 3 == 0) {
        b /= 3;
    } else {
        c /= 3;
    }
    
    if (a % 2 == 0) {
        a /= 2;
    } else if (b % 2 == 0) {
        b /= 2;
    } else {
        c /= 2;
    }
    
    return a * b * c;
}

int64_t countTriangles(int n) {
    if (n <= 0) {
        return 0;
    }

    int64_t up = sum_triangular(n);

    int64_t m = (n - 1) / 2;
    int64_t a = m;
    int64_t b = m + 1;
    int64_t c = 4 * m + 5;
    
    if (a % 2 == 0) {
        a /= 2;
    } else if (b % 2 == 0) {
        b /= 2;
    } else {
        c /= 2;
    }
    
    if (a % 3 == 0) {
        a /= 3;
    } else if (b % 3 == 0) {
        b /= 3;
    } else {
        c /= 3;
    }
    
    int64_t down = a * b * c;

    int64_t both = 0;
    if (n >= 4) {
        int64_t k = (n - 3) / 2;
        int64_t sum1 = sum_series(k);
        
        int64_t s2a = k;
        int64_t s2b = k + 1;
        int64_t s2c = 2 * k + 1;
        
        if (s2a % 2 == 0) {
            s2a /= 2;
        } else if (s2b % 2 == 0) {
            s2b /= 2;
        } else {
            s2c /= 2;
        }
        
        if (s2a % 3 == 0) {
            s2a /= 3;
        } else if (s2b % 3 == 0) {
            s2b /= 3;
        } else {
            s2c /= 3;
        }
        
        int64_t sum2 = s2a * s2b * s2c;
        int64_t sum_tri = (sum1 + sum2) / 2;
        both = 2 * sum_tri;
    }

    return up + down + both;
}

int main(void) {
    int n;

    printf("Enter side length: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Side length must be non-negative\n");
        return EXIT_FAILURE;
    }

    int64_t result = countTriangles(n);
    printf("Maximum equilateral triangles: %" PRId64 "\n", result);

    return EXIT_SUCCESS;
}