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
    int list1[] = {1, 2, 3, 1, 2, 3, 4, 5, 1};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int result1 = max_length(list1, size1);
    printf("%d\n", result1);

    int list2[] = {5, 4, 3, 2, 1};
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int result2 = max_length(list2, size2);
    printf("%d\n", result2);

    int *list3 = NULL;
    int size3 = 0;
    int result3 = max_length(list3, size3);
    printf("%d\n", result3);

    return 0;
}