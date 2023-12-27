#include <stdio.h>

int findMaxSublistLength(const int arr[], int n) {
    int maxLen = 0;
    int len = 1;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i-1]){
            len++;
        } else {
            if (len > maxLen) {
                maxLen = len;
            }
            len = 1;
        }
    }
    
    if (len > maxLen) {
        maxLen = len;
    }
    
    return maxLen;
}

int main() {
    const int arr[] = {1, 2, 3, 5, 4, 9, 7, 8, 10};
    int n = sizeof(arr)/sizeof(arr[0]);

    int maxLength = findMaxSublistLength(arr, n);

    printf("Maximum length of sublist: %d\n", maxLength);

    return 0;
}