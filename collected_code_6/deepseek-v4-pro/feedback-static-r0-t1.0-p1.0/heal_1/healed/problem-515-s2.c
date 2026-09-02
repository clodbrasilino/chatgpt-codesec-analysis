#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isSubsetSumDivisibleByM(const int arr[], int n, int m) {
    if (m <= 0) {
        return false;
    }
    
    if (n == 0) {
        return false;
    }
    
    bool *dp = (bool *)calloc(m, sizeof(bool));
    if (dp == NULL) {
        return false;
    }
    
    dp[0] = true;
    
    for (int i = 0; i < n; i++) {
        bool *temp = (bool *)calloc(m, sizeof(bool));
        if (temp == NULL) {
            free(dp);
            return false;
        }
        
        for (int j = 0; j < m; j++) {
            if (dp[j]) {
                temp[j] = true;
                int rem = ((j + arr[i]) % m + m) % m;
                temp[rem] = true;
            }
        }
        
        free(dp);
        dp = temp;
    }
    
    bool result = dp[0];
    free(dp);
    return result;
}

int main(void) {
    int arr1[] = {3, 1, 7, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int m1 = 6;
    
    if (isSubsetSumDivisibleByM(arr1, n1, m1)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    int arr2[] = {1, 2, 3, 4};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int m2 = 10;
    
    if (isSubsetSumDivisibleByM(arr2, n2, m2)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    int arr3[] = {5, 5, 5, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int m3 = 7;
    
    if (isSubsetSumDivisibleByM(arr3, n3, m3)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    return 0;
}