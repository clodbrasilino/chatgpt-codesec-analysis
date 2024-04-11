#include <stdio.h>
#include <stdbool.h>

#define SIZE 5

bool checkElementInTuple(int tuple[], int size, int element) {
    for(int i = 0; i < size; i++) {
        if(tuple[i] == element) {
            return true;
        }
    }
    return false;
}

int main() {
    int tuple[SIZE] = {1, 2, 3, 4, 5};
    int element = 3;

    if(checkElementInTuple(tuple, SIZE, element)) {
        printf("Element is in the tuple.\n");
    } else {
        printf("Element is not in the tuple.\n");
    }

    return 0;
}