#include<stdio.h>

int isSubsetSum(int set[], int n, int sum)
{
    if (sum == 0)
        return 1;
    if (n == 0 && sum != 0)
        return 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'set[n-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (set[n-1] > sum)
        return isSubsetSum(set, n-1, sum);
    return isSubsetSum(set, n-1, sum) ||
           isSubsetSum(set, n-1, sum-set[n-1]);
}

int main()
{
    int set[] = {3, 34, 4, 12, 5, 2};
    int sum = 9;
    int n = sizeof(set)/sizeof(set[0]);
    if (isSubsetSum(set, n, sum) == 1)
        printf("Found a subset with given sum\n");
    else
        printf("No subset with given sum\n");
    return 0;
}