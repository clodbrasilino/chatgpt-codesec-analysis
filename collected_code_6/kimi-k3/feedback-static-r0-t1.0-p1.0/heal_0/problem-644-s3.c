#include <stdio.h>
#include <stdlib.h>

void reverse_array_upto(int *arr, size_t size, size_t pos)
{
    size_t start = 0;
    size_t end;
    int temp;

    if (arr == NULL || size == 0 || pos >= size) {
        return;
    }

    end = pos;

    while (start < end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t pos = 4;
    size_t i;

    printf("Original array: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    reverse_array_upto(arr, size, pos);

    printf("Array after reversing up to position %zu: ", pos);
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}