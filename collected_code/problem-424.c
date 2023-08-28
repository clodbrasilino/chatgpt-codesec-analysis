#include <stdio.h>
#include <string.h>

void extractRearIndexElement(char array[][100], int size) {
    for (int i = 0; i < size; i++) {
        int length = strlen(array[i]);
        if (length > 0) {
            printf("%c\n", array[i][length-1]);
        }
    }
}