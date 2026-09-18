#include <stdio.h>
#include <stdbool.h>

bool findTriplets(int arr[], int n, int sum)
{
    for (int i = 0; i < n - 2; i++)
    {
        for (int j = i + 1; j < n - 1; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                if (arr[i] + arr[j] + arr[k] == sum)
                {
                    printf("Triplets are %d, %d, %d", arr[i], arr[j], arr[k]);
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr)/sizeof(arr[0]);
    int sum = 18;
    bool result = findTriplets(arr, n, sum);
    if (!result) {
        printf("No triplet with sum %d found.", sum);
    }
    return 0;
}