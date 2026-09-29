#include <stdio.h>
#include <stdlib.h>

int max_length(const int *list, int size) {
    if (list == NULL || size <= 0) {
        return 0;
    }

    int max_len = 1;
    int current_len = 1;

    for (int i = 1; i < size; i++) {
        if (list[i] > list[i - 1]) {
            current_len++;
        } else {
            if (current_len > max_len) {
                max_len = current_len;
            }
            current_len = 1;
        }
    }

    if (current_len > max_len) {
        max_len = current_len;
    }

    return max_len;
}

int main() {
    int arr1[] = {1, 2, 3, 1, 2, 3, 4, 5, 1};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = max_length(arr1, size1);
    printf("%d\n", result1);

    int arr2[] = {5, 4, 3, 2, 1};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = max_length(arr2, size2);
    printf("%d\n", result2);

    int result3 = max_length(NULL, 0);
    printf("%d\n", result3);

    return 0;
}