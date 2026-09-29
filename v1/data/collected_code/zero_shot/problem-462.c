#include <stdio.h>

// Function to swap two elements in an array
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to print an array
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Function to find all possible combinations of elements of a given list
void combinationUtil(int arr[], int data[], int start, int end, int index, int r)
{
    if (index == r)
    {
        printArray(data, r);
        return;
    }

    for (int i = start; i <= end && end - i + 1 >= r - index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i + 1, end, index + 1, r);
    }
}

// Function to generate all possible combinations of elements of a given list
void combinations(int arr[], int n, int r)
{
    int data[r];
    combinationUtil(arr, data, 0, n - 1, 0, r);
}

// Main function
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int r = 3;
    combinations(arr, n, r);
    return 0;
}