#include <stdio.h>
#include <stdbool.h>

#define SIZE 5

bool checkElement(int tuple[], int size, int element) {
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

    if(checkElement(tuple, SIZE, element)) {
        printf("Element found in the tuple.\n");
    } else {
        printf("Element not found in the tuple.\n");
    }

    return 0;
}