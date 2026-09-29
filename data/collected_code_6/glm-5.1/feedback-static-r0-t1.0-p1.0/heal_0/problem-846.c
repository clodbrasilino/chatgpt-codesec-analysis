#include <stdio.h>
#include <stdlib.h>

int find_min_platforms(int arr[], int dep[], int n) {
    if (n <= 0) {
        return 0;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            if (dep[j] > dep[j + 1]) {
                int temp = dep[j];
                dep[j] = dep[j + 1];
                dep[j + 1] = temp;
            }
        }
    }

    int platforms_needed = 1;
    int result = 1;
    int i = 1;
    int j = 0;

    while (i < n && j < n) {
        if (arr[i] <= dep[j]) {
            platforms_needed++;
            if (platforms_needed > result) {
                result = platforms_needed;
            }
            i++;
        } else {
            platforms_needed--;
            j++;
        }
    }

    return result;
}

int main() {
    int arr[] = {900, 940, 950, 1100, 1500, 1800};
    int dep[] = {910, 1200, 1120, 1130, 1900, 2000};
    int n = sizeof(arr) / sizeof(arr[0]);

    int min_platforms = find_min_platforms(arr, dep, n);

    printf("%d\n", min_platforms);

    return 0;
}