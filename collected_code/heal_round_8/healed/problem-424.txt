#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_ARRAY_SIZE 100
#define ARRAY_LENGTH 3

void extractRearIndexElement(const char array[][MAX_ARRAY_SIZE], int size);

int main() {

    char array[ARRAY_LENGTH][MAX_ARRAY_SIZE] = {"hello", "world", "C"};
    extractRearIndexElement(array, ARRAY_LENGTH);
    return 0;
}

void extractRearIndexElement(const char array[][MAX_ARRAY_SIZE], int size){
    assert(array != NULL && size <= ARRAY_LENGTH && size >= 0);
    for (int i = 0; i < size; i++) {
        int length = strnlen(array[i], MAX_ARRAY_SIZE - 1);
        if (length > 0 && length <= MAX_ARRAY_SIZE) {
            printf("%c\n", array[i][length-1]);
        }
    }
}