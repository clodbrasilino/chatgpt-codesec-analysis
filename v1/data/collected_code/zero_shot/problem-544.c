#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flattenTuple(int* tuple, int size) {
    char* str = malloc(size * sizeof(char));
    *str = '\0';
    for (int i = 0; i < size; i++) {
        char num[20];
        sprintf(num, "%d", tuple[i]);
        strcat(str, num);
        if (i < size - 1) {
            strcat(str, ",");
        }
    }
    return str;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    char* result = flattenTuple(tuple, size);
    printf("%s\n", result);
    free(result);
    return 0;
}