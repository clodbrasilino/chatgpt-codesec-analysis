#include <stdio.h>
#include <stdlib.h>

void reverseArray(int *arr, int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int main() {
    int n, pos;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    if (n <= 0) {
        fprintf(stderr, "Invalid number of elements.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the position up to which to reverse: ");
    scanf("%d", &pos);
    if (pos < 0 || pos >= n) {
        fprintf(stderr, "Invalid position.\n");
        free(arr);
        return 1;
    }

    reverseArray(arr, 0, pos);

    printf("Reversed array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}