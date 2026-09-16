#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#define MAX_SIZE 1000

long long maxProductIncreasingSubsequence(const int arr[], int n) {
    if (arr == NULL || n <= 0 || n > MAX_SIZE) {
        return LLONG_MIN;
    }
    
    long long *dp = (long long *)malloc((size_t)n * sizeof(long long));
    if (dp == NULL) {
        return LLONG_MIN;
    }
    
    for (int i = 0; i < n; i++) {
        dp[i] = arr[i];
    }
    
    long long maxProduct = LLONG_MIN;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                if (dp[j] != 0 && arr[i] != 0) {
                    if (dp[j] > 0 && arr[i] > 0) {
                        if (dp[j] > LLONG_MAX / arr[i]) {
                            free(dp);
                            return LLONG_MIN;
                        }
                    } else if (dp[j] < 0 && arr[i] < 0) {
                        if (dp[j] < LLONG_MAX / arr[i]) {
                            free(dp);
                            return LLONG_MIN;
                        }
                    } else if (dp[j] < 0 && arr[i] > 0) {
                        if (dp[j] < LLONG_MIN / arr[i]) {
                            free(dp);
                            return LLONG_MIN;
                        }
                    } else if (dp[j] > 0 && arr[i] < 0) {
                        if (arr[i] < LLONG_MIN / dp[j]) {
                            free(dp);
                            return LLONG_MIN;
                        }
                    }
                }
                
                long long product = dp[j] * arr[i];
                if (product > dp[i]) {
                    dp[i] = product;
                }
            }
        }
        if (dp[i] > maxProduct) {
            maxProduct = dp[i];
        }
    }
    
    free(dp);
    return maxProduct;
}

int main(void) {
    int n;
    int arr[MAX_SIZE];
    
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n <= 0 || n > MAX_SIZE) {
        fprintf(stderr, "Error: Invalid array size\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Error: Invalid input\n");
            return EXIT_FAILURE;
        }
    }
    
    long long result = maxProductIncreasingSubsequence(arr, n);
    
    if (result == LLONG_MIN) {
        fprintf(stderr, "Error: Overflow occurred or invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Maximum product of increasing subsequence: %lld\n", result);
    
    return EXIT_SUCCESS;
}