#include <stdio.h>
#include <stdlib.h>

int findPlatform(int arr[], int dep[], int n)
{
    int plat_needed = 1, result = 1;
    int i = 1, j = 0;

    for (i = 0; i < n; i++) {
        plat_needed = 1;

        for (j = i + 1; j < n; j++) {
            if ((arr[i] >= arr[j] && arr[i] <= dep[j]) || 
               (arr[j] >= arr[i] && arr[j] <= dep[i]))
                plat_needed++;
        }

        if (plat_needed > result)
            result = plat_needed;
    }

    return result;
}

int main()
{
    int arr[] = {900, 940, 950, 1100, 1500, 1800};
    int dep[] = {910, 1200, 1120, 1130, 1900, 2000};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Minimum Number of Platforms Required = %d", findPlatform(arr, dep, n));
    return 0;
}