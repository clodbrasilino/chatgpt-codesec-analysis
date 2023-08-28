#include <stdio.h>

void findSecondSmallest(int arr[], int n)
{
    if (n < 2)
    {
        printf("Invalid input\n");
        return;
    }

    int smallest = arr[0];
    int secondSmallest = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] < smallest)
        {
            secondSmallest = smallest;
            smallest = arr[i];
        }
        else if (arr[i] < secondSmallest && arr[i] != smallest)
        {
            secondSmallest = arr[i];
        }
    }

    printf("The second smallest number is %d\n", secondSmallest);
}

int main()
{
    int arr[] = {5, 2, 8, 0, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    findSecondSmallest(arr, n);

    return 0;
}