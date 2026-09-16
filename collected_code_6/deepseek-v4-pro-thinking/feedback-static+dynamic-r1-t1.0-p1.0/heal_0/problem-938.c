#include <stdio.h>
#include <limits.h>

int findThreeClosest(const int arr1[], int len1,
                     const int arr2[], int len2,
                     const int arr3[], int len3,
                     int *elem1, int *elem2, int *elem3)
{
    int i, j, k;
    int best_i, best_j, best_k;
    long long best_diff = LLONG_MAX;

    if (arr1 == NULL || arr2 == NULL || arr3 == NULL ||
        elem1 == NULL || elem2 == NULL || elem3 == NULL)
        return 0;

    if (len1 <= 0 || len2 <= 0 || len3 <= 0)
        return 0;

    i = 0;
    j = 0;
    k = 0;
    best_i = 0;
    best_j = 0;
    best_k = 0;

    while (i < len1 && j < len2 && k < len3)
    {
        int val1 = arr1[i];
        int val2 = arr2[j];
        int val3 = arr3[k];
        int min_val = val1 < val2 ? (val1 < val3 ? val1 : val3) : (val2 < val3 ? val2 : val3);
        int max_val = val1 > val2 ? (val1 > val3 ? val1 : val3) : (val2 > val3 ? val2 : val3);
        long long diff = (long long)max_val - (long long)min_val;

        if (diff < best_diff)
        {
            best_diff = diff;
            best_i = i;
            best_j = j;
            best_k = k;
            if (best_diff == 0)
                break;
        }

        if (val1 <= val2 && val1 <= val3)
            i++;
        else if (val2 <= val1 && val2 <= val3)
            j++;
        else
            k++;
    }

    *elem1 = arr1[best_i];
    *elem2 = arr2[best_j];
    *elem3 = arr3[best_k];

    return 1;
}

int main(void)
{
    int arr1[] = {1, 5, 10, 20, 40, 80};
    int arr2[] = {6, 7, 20, 80, 100};
    int arr3[] = {3, 4, 15, 20, 30, 70, 80, 120};
    int len1 = (int)(sizeof(arr1) / sizeof(arr1[0]));
    int len2 = (int)(sizeof(arr2) / sizeof(arr2[0]));
    int len3 = (int)(sizeof(arr3) / sizeof(arr3[0]));
    int elem1, elem2, elem3;

    if (findThreeClosest(arr1, len1, arr2, len2, arr3, len3,
                         &elem1, &elem2, &elem3))
    {
        printf("%d %d %d\n", elem1, elem2, elem3);
    }

    return 0;
}