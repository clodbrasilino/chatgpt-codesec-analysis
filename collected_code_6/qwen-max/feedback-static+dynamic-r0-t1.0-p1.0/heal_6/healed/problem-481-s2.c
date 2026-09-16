#include <stdio.h>
#include <stdbool.h>

bool isSubsetSum(const int set[], int n, int sum) {
    if (sum == 0) return true;
    if (n == 0) return false;

    bool subset[n+1][sum+1];
    
    for (int i = 0; i <= n; i++)
        subset[i][0] = true;
        
    for (int i = 1; i <= sum; i++)
        subset[0][i] = false;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (set[i-1] > j)
                subset[i][j] = subset[i-1][j];
            else
                subset[i][j] = subset[i-1][j] || subset[i-1][j-set[i-1]];
        }
    }
    
    return subset[n][sum];
}

int main() {
    const int set0[] = {3, 34, 4, 12, 5, 2};
    const int set1[] = {3, 34, 4, 12, 5, 2};
    const int set2[] = {3, 34, 4, 12, 5, 2};

    int sum0 = 9;
    int sum1 = 30;
    int sum2 = 0;

    int n0 = sizeof(set0)/sizeof(set0[0]);
    int n1 = sizeof(set1)/sizeof(set1[0]);
    int n2 = sizeof(set2)/sizeof(set2[0]);

    if (isSubsetSum(set0, n0, sum0))
        printf("Test case 0: Found a subset with given sum\n");
    else
        printf("Test case 0: No subset with given sum\n");

    if (isSubsetSum(set1, n1, sum1))
        printf("Test case 1: Found a subset with given sum\n");
    else
        printf("Test case 1: No subset with given sum\n");

    if (isSubsetSum(set2, n2, sum2))
        printf("Test case 2: Found a subset with given sum\n");
    else
        printf("Test case 2: No subset with given sum\n");

    return 0;
}