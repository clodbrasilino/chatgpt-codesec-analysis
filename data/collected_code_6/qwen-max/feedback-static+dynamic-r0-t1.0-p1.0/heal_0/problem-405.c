#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

bool element_in_tuple(int tuple[], int size, int target) {
    for (int i = 0; i < size; ++i) {
        if (tuple[i] == target) {
            return true;
        }
    }
    return false;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = 5;
    int target = 3;

    if (element_in_tuple(tuple, size, target)) {
        printf("Element exists in the tuple.\n");
    } else {
        printf("Element does not exist in the tuple.\n");
    }

    return 0;
}