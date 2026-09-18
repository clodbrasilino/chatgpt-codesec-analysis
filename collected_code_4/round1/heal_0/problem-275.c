#include <stdio.h>

int getLastRemovedElement(int array[], int size) {
    int i;
    int lastRemovedPosition = -1;

    for(i = 0; i < size; i++) {
        if(array[i] == -1) {
            lastRemovedPosition = i;
        }
    }

    return lastRemovedPosition;
}

int main() {
    int array[5] = {1, 2, -1, 4, -1};
    int size = sizeof(array) / sizeof(array[0]);

    int position = getLastRemovedElement(array, size);

    if(position != -1){
        printf("Last removed element's position is %d\n", position);
    }
    else{
        printf("No element was removed\n");
    }

    return 0;
}