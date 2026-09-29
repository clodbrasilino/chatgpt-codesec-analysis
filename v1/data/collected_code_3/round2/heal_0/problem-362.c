#include <stdio.h>
#include <stdlib.h>

int maxOccurrence(int* arr, int n) {
    int max = 0, res = arr[0], count;

    for (int i = 0; i < n; i++) {
        count = 1;
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j])
                count++;
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
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));

    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int maxOccur = maxOccurrence(arr, n);
    printf("The number with maximum occurrences is: %d\n", maxOccur);

    free(arr);
    return 0;
}