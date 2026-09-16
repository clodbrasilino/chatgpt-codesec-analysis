#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int find_equilibrium_index(int arr[], int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    long long total_sum = 0;
    long long left_sum = 0;

    for (int i = 0; i < size; ++i) {
        total_sum += arr[i];
    }

    for (int i = 0; i < size; ++i) {
        total_sum -= arr[i];

        if (left_sum == total_sum) {
            return i;
        }

        left_sum += arr[i];
    }

    return -1;
}

int main(void) {
    int arr[] = {-7, 1, 5, 2, -4, 3, 0};
    int size = sizeof(arr) / sizeof(arr[0]);

    int equilibrium_index = find_equilibrium_index(arr, size);

    if (equilibrium_index != -1) {
        printf("Equilibrium index: %d\n", equilibrium_index);
    } else {
        printf("No equilibrium index found.\n");
    }

    return 0;
}