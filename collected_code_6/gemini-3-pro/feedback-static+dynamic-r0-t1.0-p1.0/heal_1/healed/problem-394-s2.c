#include <stdio.h>
#include <stdbool.h>

bool isDistinct(const int tuple[], int size) {
    if (tuple == NULL || size <= 0) {
        return false;
    }

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (tuple[i] == tuple[j]) {
                return false;
            }
        }
    }
    return true;
}

int main(void) {
    int tuple1[] = {1, 2, 3, 4, 5};
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);

    int tuple2[] = {1, 2, 3, 2, 5};
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    if (isDistinct(tuple1, size1)) {
        printf("Tuple 1 is distinct.\n");
    } else {
        printf("Tuple 1 is not distinct.\n");
    }

    if (isDistinct(tuple2, size2)) {
        printf("Tuple 2 is distinct.\n");
    } else {
        printf("Tuple 2 is not distinct.\n");
    }

    return 0;
}