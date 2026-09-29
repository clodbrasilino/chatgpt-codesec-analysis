#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
double find_zero_ratio(int *arr, int size) {
    int zero_count = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == 0) {
            zero_count++;
        }
    }
    return (size > 0) ? (double)zero_count / size : 0.0;
}

int main() {
    int arr[] = {0, 1, 0, 2, 0, 3, 4};
    int size = sizeof(arr) / sizeof(arr[0]);
    double ratio = find_zero_ratio(arr, size);
    printf("Ratio of zeroes: %.2f\n", ratio);
    return 0;
}