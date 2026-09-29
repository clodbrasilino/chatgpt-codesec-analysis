#include <stdio.h>
#include <stdbool.h>

bool isSubsetSum(int set[], int n, int sum) {
    if (sum == 0)
        return true;
    if (n == 0 && sum != 0)
        return false;

    if (set[n - 1] > sum)
        return isSubsetSum(set, n - 1, sum);

    return isSubsetSum(set, n - 1, sum) || isSubsetSum(set, n - 1, sum - set[n - 1]);
}

int main() {
    int set[] = {3, 34, 4, 12, 5, 2};
    int targetSum = 9;
    int setSize = sizeof(set) / sizeof(set[0]);
    
    if (isSubsetSum(set, setSize, targetSum) == true)
        printf("Found a subset with given sum\n");
    else
        printf("No subset with given sum\n");

    return 0;
}