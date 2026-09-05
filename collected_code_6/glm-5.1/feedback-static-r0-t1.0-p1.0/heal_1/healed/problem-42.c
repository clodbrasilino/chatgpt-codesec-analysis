#include <stdio.h>
#include <stdlib.h>

int findSumOfRepeatedElements(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    int *temp = malloc(size * sizeof(int));
    if (temp == NULL) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        temp[i] = arr[i];
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    int sum = 0;
    size_t i = 0;
    while (i < size) {
        size_t count = 1;
        while (i + count < size && temp[i + count] == temp[i]) {
            count++;
        }
        if (count > 1) {
            sum += temp[i] * count;
        }
        i += count;
    }

    free(temp);
    return sum;
}

int main(void) {
    int arr[] = {4, 2, 4, 5, 2, 3, 1, 2};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int result = findSumOfRepeatedElements(arr, size);

    printf("%d\n", result);

    return 0;
}