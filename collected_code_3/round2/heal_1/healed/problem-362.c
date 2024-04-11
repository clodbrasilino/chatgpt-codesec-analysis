#include <stdio.h>
#include <stdlib.h>

int maxOccurrence(int* arr, int n) {
    if(arr == NULL || n <= 0) {
        return 0;
    }

    int max = 0, res = arr[0], count;

    for (int i = 0; i < n; i++) {
        count = 1;
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }

        if (count > max) {
            max = count;
            res = arr[i];
        }
    }
    return res;
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input.\n");
            free(arr);
            return 1;
        }
    }

    int maxOccur = maxOccurrence(arr, n);
    printf("The number with maximum occurrences is: %d\n", maxOccur);

    free(arr);
    return 0;
}