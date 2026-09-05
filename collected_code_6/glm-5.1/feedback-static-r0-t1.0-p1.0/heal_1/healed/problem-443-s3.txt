#include <stdio.h>
#include <limits.h>

int find_largest_negative(const int *list, size_t size) {
    int largest = INT_MIN;
    int found = 0;

    if (list == NULL || size == 0) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        if (list[i] < 0) {
            if (!found || list[i] > largest) {
                largest = list[i];
                found = 1;
            }
        }
    }

    if (!found) {
        return -1;
    }

    return largest;
}

int main() {
    int arr[] = {3, -1, -7, 4, -2, 0, 8, -5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int result = find_largest_negative(arr, size);

    if (result == -1) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}