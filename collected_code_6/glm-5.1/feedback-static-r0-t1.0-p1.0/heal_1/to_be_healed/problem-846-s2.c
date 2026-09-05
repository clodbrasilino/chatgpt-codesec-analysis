#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 *  Parameter 'dep' can be declared as const array [constParameter]
 */
int find_min_platforms(int arr[], int dep[], int n) {
    if (n <= 0) return 0;

    int *count = (int *)calloc(2361, sizeof(int));
    if (count == NULL) return -1;

    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
        count[dep[i] + 1]--;
    }

    int min_platforms = 0;
    int current_platforms = 0;

    for (int i = 0; i < 2361; i++) {
        current_platforms += count[i];
        if (current_platforms > min_platforms) {
            min_platforms = current_platforms;
        }
    }

    free(count);
    return min_platforms;
}

int main() {
    int arr[] = {900, 940, 950, 1100, 1500, 1800};
    int dep[] = {910, 1200, 1120, 1130, 1900, 2000};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = find_min_platforms(arr, dep, n);
    if (result >= 0) {
        printf("%d\n", result);
    }

    return 0;
}