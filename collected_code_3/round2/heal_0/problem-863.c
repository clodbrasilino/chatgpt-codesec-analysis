#include <stdio.h>
#include <stdlib.h>

int findLongestConseqSubseq(int arr[], int n)
{
    int visited[100000] = {0};
    int i;
    for (i = 0; i < n; i++)
        visited[arr[i]] = 1;
    int ans = 0;
    for (i = 0; i < n; i++)
    {
        if (visited[arr[i]] == 0)
            continue;
        int count = 1;
        visited[arr[i]] = 0;
        int j = arr[i];
        while (visited[j + 1] == 1)
        {
            count++;
            visited[j + 1] = 0;
            j++;
        }
        j = arr[i];
        while (visited[j - 1] == 1)
        {
            count++;
            visited[j - 1] = 0;
            j--;
        }
        ans = ans > count ? ans : count;
    }
    return ans;
}

int main()
{
    int arr[] = {1, 9, 3, 10, 4, 20, 2};
    int n = sizeof arr / sizeof arr[0];
    printf("Length of the Longest consecutive subsequence is %d\n",
           findLongestConseqSubseq(arr, n));
    return 0;
}