#include <stdio.h>
#include <stdlib.h>
/* Possible weaknesses found:
 *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
 */
#include <stdint.h>

long long sum_of_products_subarrays(const int arr[], int n) {
    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        long long product = 1;
        for (int j = i; j < n; j++) {
            /* Possible weaknesses found:
             *  use of undeclared identifier 'LLONG_MAX'
             *  'LLONG_MAX' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             */
            if (product > LLONG_MAX / llabs(arr[j]) || 
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'LLONG_MIN'
                 *  'LLONG_MIN' undeclared (first use in this function)
                 *  'LLONG_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
                 */
                (product < LLONG_MIN / llabs(arr[j]))) {
                break;
            }
            product *= arr[j];
            /* Possible weaknesses found:
             *  use of undeclared identifier 'LLONG_MAX'
             */
            if ((arr[j] > 0 && total_sum > LLONG_MAX - product) || 
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'LLONG_MIN'
                 */
                (arr[j] < 0 && total_sum < LLONG_MIN - product)) {
                break;
            }
            total_sum += product;
        }
    }
    return total_sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    if (n <= 0) {
        return 0;
    }

    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }

    long long result = sum_of_products_subarrays(arr, n);
    printf("%lld\n", result);

    free(arr);
    return 0;
}