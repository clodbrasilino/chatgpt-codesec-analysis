#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'tuple' can be declared as pointer to const [constParameterPointer]
 */
bool is_distinct(int *tuple, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (tuple[i] == tuple[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int tuple1[] = {1, 2, 3, 4};
    int tuple2[] = {1, 2, 2, 4};

    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    if (is_distinct(tuple1, size1)) {
        printf("Tuple1 is distinct\n");
    } else {
        printf("Tuple1 is not distinct\n");
    }

    if (is_distinct(tuple2, size2)) {
        printf("Tuple2 is distinct\n");
    } else {
        printf("Tuple2 is not distinct\n");
    }

    return 0;
}