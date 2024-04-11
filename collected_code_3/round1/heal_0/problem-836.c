#include <stdio.h>

int maxSubArraySum(int a[], int size)
{
    int max_so_far = a[0];
    int curr_max = a[0];
    int start =0, end = 0, s=0;

    for (int i = 1; i < size; i++)
    {
        if (curr_max + a[i] > a[i]){
            curr_max = curr_max + a[i];
        }
        else{
            curr_max = a[i];
            s = i;
        }

        if (max_so_far < curr_max){
            max_so_far = curr_max;
            start = s;
            end = i;
        }
    }
    return (end - start + 1);
}

int main()
{
    int a[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(a)/sizeof(a[0]);
    int max_sum = maxSubArraySum(a, n);
    printf("Length of the subarray having maximum sum is %d\n", max_sum);
    return 0;
}