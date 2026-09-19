#include <stdio.h>
#include <stdlib.h>
/* Possible weaknesses found:
 *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
 */
#include <stdint.h>

long long sumOfSubarrayProducts(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    
    long long totalSum = 0;
    
    for (int i = 0; i < n; i++) {
        long long product = 1;
        for (int j = i; j < n; j++) {
            /* Possible weaknesses found:
             *  use of undeclared identifier 'LLONG_MAX'
             *  'LLONG_MAX' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             */
            if (arr[j] != 0 && product > LLONG_MAX / llabs((long long)arr[j])) {
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'LLONG_MAX'
                 */
                product = LLONG_MAX;
            /* Possible weaknesses found:
             *  'LLONG_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
             *  use of undeclared identifier 'LLONG_MIN'
             *  'LLONG_MIN' undeclared (first use in this function)
             */
            } else if (arr[j] != 0 && product < LLONG_MIN / llabs((long long)arr[j])) {
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'LLONG_MIN'
                 */
                product = LLONG_MIN;
            } else {
                product *= arr[j];
            }
            
            /* Possible weaknesses found:
             *  use of undeclared identifier 'LLONG_MAX'
             */
            if (product > 0 && totalSum > LLONG_MAX - product) {
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'LLONG_MAX'
                 */
                totalSum = LLONG_MAX;
            /* Possible weaknesses found:
             *  use of undeclared identifier 'LLONG_MIN'
             */
            } else if (product < 0 && totalSum < LLONG_MIN - product) {
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'LLONG_MIN'
                 */
                totalSum = LLONG_MIN;
            } else {
                totalSum += product;
            }
        }
    }
    
    return totalSum;
}

int main(void) {
    int n;
    
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if ((size_t)n > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    int *arr = malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }
    
    long long result = sumOfSubarrayProducts(arr, n);
    printf("%lld\n", result);
    
    free(arr);
    return EXIT_SUCCESS;
}