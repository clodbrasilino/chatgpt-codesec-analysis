#include <stdio.h>
#include <string.h>

int findMinRotations(char* str) {
    int len = strlen(str);
    char* concat = (char*)malloc(sizeof(char) * (len * 2 + 1));
    strcpy(concat, str);
    strcat(concat, str);

    int rotations = 0;
    int k = 1;

    while (k < len) {
        int i = 0;
        int j = k;

        while (j < len * 2 && concat[i] <= concat[j]) {
            if (concat[i] < concat[j]) {
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
    char* str = "abcd";
    int minRotations = findMinRotations(str);

    printf("Minimum number of rotations required: %d\n", minRotations);

    return 0;
}