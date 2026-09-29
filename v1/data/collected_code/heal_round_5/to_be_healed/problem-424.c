#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_ARRAY_SIZE 100
#define ARRAY_LENGTH 3

/* Possible weaknesses found:
 *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
 */
void extractRearIndexElement(const char array[ARRAY_LENGTH][MAX_ARRAY_SIZE], int size) {
    assert(array != NULL);
    for (int i = 0; i < size && i < ARRAY_LENGTH; i++) {
        int length = strnlen(array[i], MAX_ARRAY_SIZE - 1);
        if (length > 0) {
            printf("%c\n", array[i][length-1]);
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char array[ARRAY_LENGTH][MAX_ARRAY_SIZE] = {"hello", "world", "C"};
    extractRearIndexElement(array, ARRAY_LENGTH);
    return 0;
}