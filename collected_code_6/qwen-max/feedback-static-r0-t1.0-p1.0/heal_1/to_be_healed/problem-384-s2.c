#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_smallest_frequency(int *arr, int n) {
    int min = INT_MAX;
    int freq = 0;

    for (int i = 0; i < n; ++i) {
        if (arr[i] < min) {
            min = arr[i];
            freq = 1;
        } else if (arr[i] == min) {
            freq++;
        }
    }

    return freq;
}

int main() {
    int arr[] = {3, 1, 2, 1, 4, 1, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int frequency = find_smallest_frequency(arr, n);
    printf("Frequency of the smallest value: %d\n", frequency);
    return 0;
}