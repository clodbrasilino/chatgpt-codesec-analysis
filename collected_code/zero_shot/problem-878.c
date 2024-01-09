#include <stdbool.h>
#include <stdio.h>

bool checkTuple(int tuple[], int size, int k) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (tuple[i] != 0) {
            count++;
        }
    }
    return count == k;
}

int main() {
    int tuple[] = {1, 2, 3, 0, 0, 0};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    int k = 3;

    if (checkTuple(tuple, size, k)) {
        printf("The tuple contains only %d elements.\n", k);
    } else {
        printf("The tuple does not contain only %d elements.\n", k);
    }

    return 0;
}