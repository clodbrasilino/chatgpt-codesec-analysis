#include <stdio.h>
#include <stdlib.h>

int max_length(int *list, int size) {
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
    int list[] = {1, 2, 3, 1, 2, 3, 4, 5, 1, 2};
    int size = sizeof(list) / sizeof(list[0]);

    int result = max_length(list, size);

    printf("%d\n", result);

    return 0;
}