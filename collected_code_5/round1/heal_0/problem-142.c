#include <stdio.h>

int countPairs(int *arr1, int *arr2, int *arr3, int n1, int n2, int n3, int num)
{
    int i, j, k, count = 0;

    for(i = 0; i < n1; i++)
        if(arr1[i] == num)
            count++;

    for(j = 0; j < n2; j++)
        if(arr2[j] == num)
            count++;

    for(k = 0; k < n3; k++)
        if(arr3[k] == num)
            count++;

    return count;
}

int main() 
{
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {2, 3, 4, 5, 6};
    int arr3[] = {3, 4, 5, 6, 7};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    int num = 5;

    int count = countPairs(arr1, arr2, arr3, n1, n2, n3, num);

    printf("The number: %d appears %d time(s) in the three arrays.", num, count);

    return 0;
}