#include <stdio.h>
#include <limits.h>

int find_largest_positive(const int *list, size_t size) {
    int largest = -1;
    int found_positive = 0;

    if (list == NULL || size == 0) {
        return -1;
    }

    for (size_t i = 0; i < size; ++i) {
        if (list[i] > 0) {
            if (!found_positive) {
                largest = list[i];
                found_positive = 1;
            } else if (list[i] > largest) {
                largest = list[i];
            }
        }
    }

    return largest;
}

int main(void) {
    int data[] = {-3, -1, 0, 4, 2, 9, -5, 7};
    size_t size = sizeof(data) / sizeof(data[0]);

    int result = find_largest_positive(data, size);

    if (result > 0) {
        printf("%d\n", result);
    } else {
        printf("No positive numbers found\n");
    }

    return 0;
}