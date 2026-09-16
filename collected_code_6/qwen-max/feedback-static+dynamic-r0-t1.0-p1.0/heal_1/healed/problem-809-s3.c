#include <stdio.h>
#include <stdbool.h>

bool check_tuples(const int *first, const int *second, int size) {
    for (int i = 0; i < size; i++) {
        if (second[i] >= first[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int first[] = {5, 10, 15, 20};
    int second[] = {3, 8, 12, 18};
    int size = sizeof(first) / sizeof(first[0]);

    if (check_tuples(first, second, size)) {
        printf("All elements in the second tuple are smaller than their corresponding elements in the first tuple.\n");
    } else {
        printf("Not all elements in the second tuple are smaller than their corresponding elements in the first tuple.\n");
    }

    return 0;
}