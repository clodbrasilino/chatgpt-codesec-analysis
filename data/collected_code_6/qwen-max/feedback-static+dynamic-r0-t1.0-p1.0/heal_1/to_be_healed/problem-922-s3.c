#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
void findMaxProductPair(int arr[], int n, int *x, int *y) {
    if (n < 2) return;
    
    *x = 0;
    *y = 1;
    int maxProduct = arr[0] * arr[1];
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] * arr[j] > maxProduct) {
                maxProduct = arr[i] * arr[j];
                *x = i;
                *y = j;
            }
        }
    }
}

int main() {
    int arr[] = {1, 4, 3, 6, 7, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x, y;

    findMaxProductPair(arr, n, &x, &y);

    if (x != -1 && y != -1) {
        printf("The pair with the highest product is: (%d, %d)\n", arr[x], arr[y]);
    } else {
        printf("No valid pair found\n");
    }

    return 0;
}