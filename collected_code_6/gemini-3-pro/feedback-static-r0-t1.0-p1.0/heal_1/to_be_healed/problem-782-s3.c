#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int sumOddLengthSubarrays(int* arr, int arrSize) {
    if (arr == NULL || arrSize <= 0) {
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < arrSize; i++) {
        int left_choices = i + 1;
        int right_choices = arrSize - i;
        int total_choices = left_choices * right_choices;
        int odd_subarrays = (total_choices + 1) / 2;
        sum += arr[i] * odd_subarrays;
    }
    return sum;
}

int main(void) {
    int arr[] = {1, 4, 2, 5, 3};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    int result = sumOddLengthSubarrays(arr, arrSize);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}