#include <stdio.h>
#include <stdbool.h>

bool check_tuples(const int *first, const int *second, int size) {
    for (int i = 0; i < size; ++i) {
        if (second[i] <= i || first[i] != i) {
            return false;
        }
    }
    return true;
}

int main() {
    const int first[] = {0, 1, 2, 3, 4};
    const int second[] = {1, 2, 3, 4, 5};
    int size = sizeof(first) / sizeof(first[0]);

    if (check_tuples(first, second, size)) {
        printf("All elements in the second tuple are greater than their corresponding index in the first tuple.\n");
    } else {
        printf("Not all elements in the second tuple are greater than their corresponding index in the first tuple.\n");
    }

    return 0;
}