#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

long long sum_of_products_of_subarrays(const int *arr, int n) {
    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        long long current_product = 1;
        int product_active = 1;
        for (int j = i; j < n; j++) {
            int val = arr[j];
            
            if (val == 0) {
                current_product = 1;
                product_active = 1;
                continue;
            }
            
            if (!product_active) {
                /* Possible weaknesses found:
                 *  product_active is assigned
                 *  Value stored to 'product_active' is never read [deadcode.DeadStores]
                 */
                product_active = 1;
                current_product = 1;
            }
            
            int overflow = 0;
            
            if (val > 0) {
                if (current_product > 0) {
                    if (current_product > LLONG_MAX / val) {
                        overflow = 1;
                    }
                } else {
                    if (current_product < LLONG_MIN / val) {
                        overflow = 1;
                    }
                }
            } else {
                if (current_product > 0) {
                    if (val == LLONG_MIN) {
                        overflow = 1;
                    } else {
                        long long abs_val = (val == -1) ? 1LL : -(long long)val;
                        if (current_product > LLONG_MAX / abs_val) {
                            overflow = 1;
                        }
                    }
                } else {
                    if (val == -1) {
                        if (current_product == LLONG_MIN) {
                            overflow = 1;
                        }
                    } else {
                        if (current_product < LLONG_MIN / val) {
                            overflow = 1;
                        }
                    }
                }
            }
            
            if (overflow) {
                current_product = 1;
                product_active = 0;
                continue;
            }
            
            current_product *= val;
            
            if (current_product > 0 && total_sum > LLONG_MAX - current_product) {
                current_product = 1;
                product_active = 0;
                continue;
            }
            if (current_product < 0 && total_sum < LLONG_MIN - current_product) {
                current_product = 1;
                product_active = 0;
                continue;
            }
            
            total_sum += current_product;
            /* Possible weaknesses found:
             *  Variable 'product_active' is reassigned a value before the old one has been used. [redundantAssignment]
             *  product_active is overwritten
             */
            product_active = 1;
        }
    }
    return total_sum;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Error: Invalid input size.\n");
        return EXIT_FAILURE;
    }

    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Error: Invalid array element.\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }

    long long result = sum_of_products_of_subarrays(arr, n);
    printf("%lld\n", result);

    free(arr);
    return EXIT_SUCCESS;
}