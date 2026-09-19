#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

long long sum_of_products_of_subarrays(const int *arr, int n) {
    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        long long current_product = 1;
        for (int j = i; j < n; j++) {
            int val = arr[j];
            
            /* Possible weaknesses found:
             *  Assuming that condition 'val==0' is not redundant
             */
            if (val == 0) {
                current_product = 1;
                continue;
            }
            
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (current_product == 0) {
                current_product = 1;
                continue;
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
            /* Possible weaknesses found:
             *  Condition 'val<0' is always true
             *  Condition 'val<0' is always true [knownConditionTrueFalse]
             */
            } else if (val < 0) {
                if (current_product > 0) {
                    if (val == LLONG_MIN) {
                        overflow = 1;
                    } else {
                        long long abs_val = (val == -1) ? 1 : -val;
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
                continue;
            }
            
            current_product *= val;
            
            if (current_product > 0 && total_sum > 0) {
                if (current_product > LLONG_MAX - total_sum) {
                    current_product = 1;
                    continue;
                }
            } else if (current_product < 0 && total_sum < 0) {
                if (current_product < LLONG_MIN - total_sum) {
                    current_product = 1;
                    continue;
                }
            }
            
            total_sum += current_product;
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