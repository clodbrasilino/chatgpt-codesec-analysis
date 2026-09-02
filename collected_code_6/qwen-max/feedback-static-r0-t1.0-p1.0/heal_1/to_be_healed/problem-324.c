#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int sumAlternateTuples(int *arr, int len) {
    if (arr == NULL || len <= 0) return 0;
    
    int sum = 0;
    for (int i = 0; i < len; i += 2) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int len = sizeof(arr) / sizeof(arr[0]);
    int result = sumAlternateTuples(arr, len);
    printf("Sum: %d\n", result);
    return 0;
}