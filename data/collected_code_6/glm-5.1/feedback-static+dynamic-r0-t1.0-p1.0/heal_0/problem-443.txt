#include <stdio.h>
#include <limits.h>

int find_largest_negative(int *list, size_t size) {
    int largest = INT_MIN;
    int found = 0;

    for (size_t i = 0; i < size; i++) {
        if (list[i] < 0) {
            if (!found || list[i] > largest) {
                largest = list[i];
                found = 1;
            }
        }
    }

    if (!found) {
        return 0;
    }

    return largest;
}

int main() {
    int list[] = {3, -1, -7, 5, -2, 0, 8};
    size_t size = sizeof(list) / sizeof(list[0]);

    int result = find_largest_negative(list, size);

    printf("%d\n", result);

    return 0;
}