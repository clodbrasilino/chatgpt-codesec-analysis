#include <stdio.h>

void reverseArray(int arr[], int start, int end) 
{
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int position;

    printf("Enter the position upto which you want to reverse the array:");
    scanf("%d", &position);

    if (position > n || position < 1)
    {
        printf("Invalid position.\n");
        return -1;
    }

    reverseArray(arr, 0, position - 1);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}