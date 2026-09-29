#include <stdio.h>

int kthElement(int arr1[], int arr2[], int n1, int n2, int k)
{
    if (k > n1 + n2 || k < 1)
    {
       return -1;
    }

    int i = 0, j = 0, count = 0;

    while(i < n1 && j < n2)
    {
        if(arr1[i] <= arr2[j])
		{
            count++;
            if(count == k)
			{
                return arr1[i];
            }
            i++;
        }
        else
		{
            count++;
            if(count == k)
			{
                return arr2[j];
            }
            j++;
        }
    }

    while(i < n1)
	{
        count++;
        if(count == k)
		{
            return arr1[i];
        }
        i++;
    }

    while(j < n2)
    {
        count++;
        if(count == k)
        {
            return arr2[j];
        }
        j++;
    }

    return -1;
}

int main()
{
    int arr1[] = {2, 3, 6, 7, 9};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {1, 4, 8, 10};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    int k = 5;
    int result = kthElement(arr1, arr2, n1, n2, k);

    if (result != -1)
        printf("K-th Element is %d\n", result);
    else 
        printf("Invalid k\n");

    return 0;
}