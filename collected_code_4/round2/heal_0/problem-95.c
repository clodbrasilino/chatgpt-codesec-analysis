#include <stdio.h>
#include <limits.h>

int minLenSubList(int arr[], int n, int s)
{
    int min_len = n + 1;
    for (int start = 0; start < n; start++)
    {
        int curr_sum = arr[start];
        if (curr_sum > s)
            return 1;
        for (int end = start+1; end < n; end++)
        {
            curr_sum += arr[end];
            if (curr_sum > s && (end - start + 1) < min_len)
                min_len = (end - start + 1);
        }
    }
    if(min_len <= n) {
        return min_len;
    }
    return -1;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int s = 15;
    int res = minLenSubList(arr, n, s);
    if(res != -1){
        printf("Minimum length of sublist is : %d\n", res);
    }
    else{
        printf("No sublist with sum greater than %d\n", s);
    }
    return 0;
}