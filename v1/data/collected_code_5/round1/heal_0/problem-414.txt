#include <stdio.h>
#include <stdbool.h>

bool existsInSequence(int* arr, int size, int value) {
    for(int i=0; i<size; i++) {
        if(arr[i] == value) {
            return true;
        }
    }
    return false;
}

int main() {
    int sequence[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(sequence) / sizeof(sequence[0]);

    int valueToBeChecked = 5;

    if(existsInSequence(sequence, size, valueToBeChecked)) {
        printf("Value exists in sequence.\n");
    } else {
        printf("Value does not exist in sequence.\n");
    }

    return 0;
}