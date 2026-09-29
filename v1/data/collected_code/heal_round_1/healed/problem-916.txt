#include <stdio.h>

int findTriplet(const int arr[], int n, int given)
{
    for (int i = 0; i < n - 2; i++)
    {
        for (int j = i + 1; j < n - 1; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                if (arr[i] + arr[j] + arr[k] == given)
                    return 1; 
            }
        }
    }
    
    return 0; 
}

int main()
{
    int arr[] = {1, 4, 2, 7, 5, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int given = 10;
    
    if (findTriplet(arr, n, given))
        printf("Triplet found");
    else
        printf("No triplet found");
    
    return 0;
}