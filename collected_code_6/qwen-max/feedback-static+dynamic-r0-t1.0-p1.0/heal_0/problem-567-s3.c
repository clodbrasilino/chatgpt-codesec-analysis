#include <stdbool.h>
#include <stdio.h>

bool is_sorted(int *list, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (list[i] > list[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int n = sizeof(list) / sizeof(list[0]);
    if (is_sorted(list, n)) {
        printf("The list is sorted.\n");
    } else {
        printf("The list is not sorted.\n");
    }

    int list2[] = {1, 3, 2, 4, 5};
    n = sizeof(list2) / sizeof(list2[0]);
    if (is_sorted(list2, n)) {
        printf("The list is sorted.\n");
    } else {
        printf("The list is not sorted.\n");
    }

    return 0;
}