#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int findLongestConsecutiveSubsequence(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        temp[i] = arr[i];
    }

    qsort(temp, n, sizeof(int), compare);

    int maxLen = 1;
    int currentLen = 1;

    for (int i = 1; i < n; i++) {
        if (temp[i] == temp[i - 1]) {
            continue;
        } else if (temp[i] == temp[i - 1] + 1) {
            currentLen++;
        } else {
            if (currentLen > maxLen) {
                maxLen = currentLen;
            }
            currentLen = 1;
        }
    }

    if (currentLen > maxLen) {
        maxLen = currentLen;
    }

    free(temp);
    return maxLen;
}

int main() {
    int arr1[] = {1, 9, 3, 10, 4, 20, 2};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", findLongestConsecutiveSubsequence(arr1, n1));

    int arr2[] = {36, 41, 56, 35, 44, 33, 34, 92, 43, 32, 42};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", findLongestConsecutiveSubsequence(arr2, n2));

    int arr3[] = {1, 2, 2, 3};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", findLongestConsecutiveSubsequence(arr3, n3));

    int arr4[] = {5};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", findLongestConsecutiveSubsequence(arr4, n4));

    int arr5[] = {};
    int n5 = 0;
    printf("%d\n", findLongestConsecutiveSubsequence(arr5, n5));

    return 0;
}