#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int countXorOddPairs(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if ((arr[i] ^ arr[j]) & 1) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = countXorOddPairs(arr, n);
    printf("Number of pairs with XOR as an odd number: %d\n", result);
    return 0;
}