#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int find_remainder(int arr[], int size, int n) {
    if (n <= 0 || size <= 0) {
        return -1;
    }

    long long result = 1;

    for (int i = 0; i < size; i++) {
        result = (result * (arr[i] % n)) % n;
    }

    int final_result = (int)(result % n);

    if (final_result < 0) {
        final_result += n;
    }

    return final_result;
}

int main(void) {
    int arr[] = {100, 10, 5, 25, 35, 14};
    int size = sizeof(arr) / sizeof(arr[0]);
    int n = 11;

    int remainder = find_remainder(arr, size, n);

    printf("%d\n", remainder);

    return 0;
}