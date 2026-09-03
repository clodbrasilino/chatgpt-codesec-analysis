#include <stdio.h>
#include <stddef.h>

int most_frequent(const int *list, size_t length, int *result) {
    if (list == NULL || length == 0 || result == NULL) {
        return -1;
    }

    int max_item = list[0];
    size_t max_count = 0;

    for (size_t i = 0; i < length; ++i) {
        size_t count = 0;
        for (size_t j = 0; j < length; ++j) {
            if (list[i] == list[j]) {
                ++count;
            }
        }
        if (count > max_count) {
            max_count = count;
            max_item = list[i];
        }
    }

    *result = max_item;
    return 0;
}

int main(void) {
    int list[] = {1, 3, 2, 3, 4, 3, 2};
    size_t length = sizeof(list) / sizeof(list[0]);
    int result;

    if (most_frequent(list, length, &result) == 0) {
        printf("%d\n", result);
    } else {
        printf("invalid input\n");
    }

    return 0;
}