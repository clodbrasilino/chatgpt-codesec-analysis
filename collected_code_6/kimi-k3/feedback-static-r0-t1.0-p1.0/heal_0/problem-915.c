#include <stdio.h>
#include <stdlib.h>

void rearrange(int arr[], int n)
{
    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        return;
    }

    int pos = 0;
    int neg = n - 1;
    int i;

    for (i = 0; i < n; i++) {
        if (arr[i] >= 0) {
            temp[pos++] = arr[i];
        } else {
            temp[neg--] = arr[i];
        }
    }

    for (i = 0; i < n; i++) {
        arr[i] = temp[i];
    }

    free(temp);
    temp = NULL;
}

int main(void)
{
    int arr[] = {-1, 2, -3, 4, 5, -6, -7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    printf("Original array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    rearrange(arr, n);

    printf("Rearranged array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}