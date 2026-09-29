#include <stdio.h>
#include <limits.h>

void findSmallestRange(int arr1[], int arr2[], int arr3[], int n1, int n2, int n3, int *start, int *end) {
    int i = 0, j = 0, k = 0;
    int max_diff = INT_MAX;
    int min_val = 0, max_val = 0;

    while (i < n1 && j < n2 && k < n3) {
        int minimum = (arr1[i] <= arr2[j]) ? ((arr1[i] <= arr3[k]) ? arr1[i++] : arr3[k++]) : ((arr2[j] <= arr3[k]) ? arr2[j++] : arr3[k++]);
        int maximum = (arr1[i - 1] >= arr2[j - 1]) ? ((arr1[i - 1] >= arr3[k - 1]) ? arr1[i - 1] : arr3[k - 1]) : ((arr2[j - 1] >= arr3[k - 1]) ? arr2[j - 1] : arr3[k - 1]);

        if (maximum - minimum < max_diff) {
            max_diff = maximum - minimum;
            *start = minimum;
            *end = maximum;
        }
    }
}

int main() {
    int arr1[] = {4, 7, 9, 12, 15};
    int arr2[] = {0, 8, 10, 14, 16};
    int arr3[] = {6, 12, 14, 18, 20};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    
    int start, end;
    findSmallestRange(arr1, arr2, arr3, n1, n2, n3, &start, &end);
    
    printf("The smallest range is: [%d, %d]\n", start, end);

    return 0;
}