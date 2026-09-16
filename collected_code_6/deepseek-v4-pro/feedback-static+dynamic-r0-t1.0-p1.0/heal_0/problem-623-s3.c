#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double power_of_element(double base, int exponent) {
    return pow(base, exponent);
}

int main(void) {
    int size, n;
    
    printf("Enter number of elements: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        fprintf(stderr, "Invalid size\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter exponent n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid exponent\n");
        return EXIT_FAILURE;
    }
    
    double *list = malloc((size_t)size * sizeof(*list));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        if (scanf("%lf", &list[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(list);
            return EXIT_FAILURE;
        }
    }
    
    printf("Powers:\n");
    for (int i = 0; i < size; i++) {
        printf("%.6f ", power_of_element(list[i], n));
    }
    printf("\n");
    
    free(list);
    return EXIT_SUCCESS;
}