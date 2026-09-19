#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1.99609375, got 1.9921875
  *  test case 0 failed: expected 1.9921875, got 1.984375
  *  test case 1 failed: expected 1.9375, got 1.875
  */

double geometric_sum(int n) {
    double result = 0.0;
    
    if (n < 1) {
        return 0.0;
    }
    
    result = 2.0 * (1.0 - pow(2.0, -(double)n));
    
    return result;
}

int main(void) {
    char buffer[256];
    int n;
    
    printf("Enter n: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (sscanf(buffer, "%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 1) {
        fprintf(stderr, "n must be at least 1\n");
        return EXIT_FAILURE;
    }
    
    printf("Geometric sum: %.10f\n", geometric_sum(n));
    return EXIT_SUCCESS;
}