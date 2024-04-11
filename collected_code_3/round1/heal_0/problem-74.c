#include <stdio.h>
#include <stdbool.h>

bool checkPattern(int* array, int arraySize, int* pattern, int patternSize) {
    int i, j;
    for(i = 0; i <= arraySize - patternSize; i++) {
        for(j = 0; j < patternSize; j++) {
            if(array[i + j] != pattern[j]) {
                break;
            }
        }
        if(j == patternSize) {
            return true;
        }
    }
    return false;
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int pattern[] = {4, 5, 6};
    int arraySize = sizeof(array) / sizeof(array[0]);
    int patternSize = sizeof(pattern) / sizeof(pattern[0]);

    if(checkPattern(array, arraySize, pattern, patternSize)) {
        printf("Pattern found.\n");
    } else {
        printf("Pattern not found.\n");
    }

    return 0;
}