#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_ARRAY_SIZE 100
#define ARRAY_LENGTH 3

void extractRearIndexElement(const char array[][MAX_ARRAY_SIZE], int size);

int main() {

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char array[ARRAY_LENGTH][MAX_ARRAY_SIZE] = {"hello", "world", "C"};
    if((sizeof(array)/sizeof(array[0])) <= ARRAY_LENGTH) {
        extractRearIndexElement(array, ARRAY_LENGTH);
    } else {
        printf("Array size larger than max limit");
        return -1;
    }
    
    return 0;
}

void extractRearIndexElement(const char array[][MAX_ARRAY_SIZE], int size){
    assert(array != NULL && size <= ARRAY_LENGTH && size >= 0);
    for (int i = 0; i < size; i++) {
        int length = strnlen(array[i], MAX_ARRAY_SIZE - 1);
        if (length > 0 && length < MAX_ARRAY_SIZE) {
            printf("%c\n", array[i][length-1]);
        }
    }
}