#include <stdio.h>
#include <stdbool.h>

bool isSubset(const int *tuple1, const int *tuple2, int len1, int len2) {
    for (int i = 0; i < len1; i++) {
        bool found = false;
        for (int j = 0; j < len2; j++) {
            if (tuple1[i] == tuple2[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

int main() {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {1, 2, 3, 4, 5};
    int len1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int len2 = sizeof(tuple2) / sizeof(tuple2[0]);

    if (isSubset(tuple1, tuple2, len1, len2)) {
        printf("Tuple1 is a subset of Tuple2\n");
    } else {
        printf("Tuple1 is not a subset of Tuple2\n");
    }

    return 0;
}