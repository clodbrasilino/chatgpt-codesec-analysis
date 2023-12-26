#include<stdio.h>

void swap(int *a, int *b) {
    /* Possible weaknesses found:
     *  Cannot determine that '*a' is initialized [premium-bughuntingUninit]
     */
    int temp = *a;
    /* Possible weaknesses found:
     *  Cannot determine that '*b' is initialized [premium-bughuntingUninit]
     */
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

int countOccurrences(int arr[], int n, int target) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] == target) {
            count++;
        }
    }
    return count;
}

void sortByFirstOccurrence(int arr[], int n) {
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int firstElement = arr[0];
    int numOccurrences = countOccurrences(arr, n, firstElement);
    bubbleSort(arr, n);
    while (numOccurrences > 0) {
        int i = 0;
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        while (arr[i] != firstElement) {
            i++;
        }
        int j = i;
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        while (arr[j] == firstElement) {
            j++;
        }
        bubbleSort(arr+i, j-i);
        numOccurrences--;
    }
}

int main() {
    int arr[] = {4, 2, 1, 4, 3, 4, 2, 1, 4, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    sortByFirstOccurrence(arr, n);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}