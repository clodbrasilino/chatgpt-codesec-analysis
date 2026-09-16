#include <stdio.h>
#include <stddef.h>

size_t count_in_range(const int *list, size_t length, int lower, int upper) {
    if (list == NULL || length == 0) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < length; i++) {
        if (list[i] >= lower && list[i] <= upper) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int list[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    size_t length = sizeof(list) / sizeof(list[0]);
    int lower = 5;
    int upper = 15;

    size_t result = count_in_range(list, length, lower, upper);
    printf("%zu\n", result);
    return 0;
}