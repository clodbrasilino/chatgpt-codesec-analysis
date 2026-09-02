#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int sum_of_repeated(int *arr, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (i != j && arr[i] == arr[j]) {
                count++;
                break;
            }
        }
        if (count > 0) {
            sum += arr[i];
        }
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 2, 1, 4, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = sum_of_repeated(arr, n);
    printf("%d\n", result);
    return 0;
}