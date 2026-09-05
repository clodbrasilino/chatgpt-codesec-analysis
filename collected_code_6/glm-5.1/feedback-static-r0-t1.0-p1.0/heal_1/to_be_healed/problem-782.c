#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int sumOddLengthSubarrays(int *arr, int arrSize) {
    int total = 0;
    for (int i = 0; i < arrSize; i++) {
        for (int j = i; j < arrSize; j += 2) {
            for (int k = i; k <= j; k++) {
                total += arr[k];
            }
        }
    }
    return total;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    if (argv[1] == NULL) {
        return 1;
    }
    int arrSize = argc - 1;
    int *arr = (int *)malloc(arrSize * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    for (int i = 0; i < arrSize; i++) {
        if (argv[i + 1] == NULL) {
            free(arr);
            return 1;
        }
        arr[i] = atoi(argv[i + 1]);
        if ((argv[i + 1][0] != '0' && arr[i] == 0) || arr[i] < 0) {
            free(arr);
            return 1;
        }
    }
    int result = sumOddLengthSubarrays(arr, arrSize);
    printf("%d\n", result);
    free(arr);
    return 0;
}