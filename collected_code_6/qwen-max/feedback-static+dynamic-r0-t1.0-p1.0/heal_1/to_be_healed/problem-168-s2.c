#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int findFrequency(int arr[], int n, int x) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] == x) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 2;
    int frequency = findFrequency(arr, n, x);
    printf("Frequency of %d is %d\n", x, frequency);
    return 0;
}