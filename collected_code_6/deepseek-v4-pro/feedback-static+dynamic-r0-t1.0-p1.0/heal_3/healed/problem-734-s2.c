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
            if (val == 0) {
                current_product = 1;
                continue;
            }
            
            int overflow = 0;
            if (current_product == 0) {
                current_product = 1;
                continue;
            }
            
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
            } else if (val < 0) {
                if (current_product > 0) {
                    if (-val < 0 && val != -1) {
                        long long limit = LLONG_MAX / (-val);
                        if (current_product > limit) {
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