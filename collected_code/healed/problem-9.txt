#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findMinRotations(const char* str) {
    int len = strlen(str);
    char* concat = (char*)malloc(sizeof(char) * (len * 2 + 1));

    if(concat == NULL) {
        printf("Memory Allocation Failed\n");
        return -1;
    }

    strncpy(concat, str, len);
    strncat(concat, str, len);

    concat[len*2] = '\0';

    int rotations = 0;
    int k = 1;

    while(k < len) {
        int i = 0;
        int j = k;

        while(j < len * 2 && concat[i] <= concat[j]) {
            if(concat[i] < concat[j]) {
                rotations = k;
                break;
            }
            i++;
            j++;
        }

        k++;
    }

    free(concat);
    return rotations;
}

int main() {
    const char* str = "abcd";
    int minRotations = findMinRotations(str);

    if(minRotations != -1) 
        printf("Minimum number of rotations required: %d\n", minRotations);

    return 0;
}