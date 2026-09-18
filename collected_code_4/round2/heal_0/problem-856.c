#include <stdio.h>

int min_swaps(int *arr, int n)
{
    int count_zero = 0;
    for (int i = 0; i < n; i++)
        if (arr[i] == 0)
            count_zero++;

    int cnt_now = 0, max_zero = 0;
    for (int i = 0; i < n; i++) {

        if (arr[i] == 0)
            cnt_now++;
        else
            cnt_now = 0;

        max_zero = max_zero > cnt_now ? max_zero : cnt_now;
    }

    return (count_zero - max_zero);
}

int main()
{
    int arr[] = {0, 0, 1, 0, 1, 0, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", min_swaps(arr, n));
    return 0;
}