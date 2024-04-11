#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int countSeq(int arr[], int n, int len, int sum) {
    if (len == 0)
        return sum >= 0;
    if (sum < 0)
        return 0;
    if (arr[len][sum] != -1)
        return arr[len][sum];
    int res = 0;
    for (int i = 0; i < n; i++)
        res += countSeq(arr, n, len - 1, sum - i);
    return (arr[len][sum] = res);
}

int countSeqUtil(int n, int len) {
    int arr[MAX][MAX];
    for (int i = 0; i <= len; i++)
        for (int j = 0; j <= len * n; j++)
            arr[i][j] = -1;
    int res = 0;
    for (int sum = 0; sum <= len * n; sum++)
        res += countSeq(arr, n, len, sum);
    return res;
}

int main() {
    int n = 3, len = 2;
    printf("%d", countSeqUtil(n, len));
    return 0;
}