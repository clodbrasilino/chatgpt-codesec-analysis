#include <stdio.h>
#include <limits.h>

int find_largest_positive(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return -1;
    }

    int max = -1;

    for (size_t i = 0; i < size; ++i) {
        if (list[i] > 0) {
            if (max == -1 || list[i] > max) {
                max = list[i];
            }
        }
    }

    return max;
}

int main(void) {
    int list[] = {-5, -2, 0, 12, 3, -8, 7};
    size_t size = sizeof(list) / sizeof(list[0]);

    int result = find_largest_positive(list, size);

    printf("%d\n", result);

    return 0;
}