#include <stdio.h>
#include <string.h>
#include <assert.h>

void extractRearIndexElement(const char array[][100], int size) {
    assert(array != NULL);
    for (int i = 0; i < size; i++) {
        int length = strnlen(array[i], 100);
        if (length > 0) {
            printf("%c\n", array[i][length-1]);
        }
    }
}

int main() {
    const int size = 3;
    char array[size][100] = {"hello", "world", "C"};
    extractRearIndexElement(array, size);
    return 0;
}