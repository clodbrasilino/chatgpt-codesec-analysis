#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extractStrings(char **strings, int size, int len, int *newSize) {
    char **newStrings = (char **)malloc(sizeof(char *) * size);
    *newSize = 0;

    for (int i = 0; i < size; i++) {
        if (strlen(strings[i]) == len) {
            newStrings[*newSize] = (char *)malloc(sizeof(char) * (len + 1));
            strcpy(newStrings[*newSize], strings[i]);
            (*newSize)++;
        }
    }

    newStrings = (char **)realloc(newStrings, sizeof(char *) * (*newSize));
    return newStrings;
}

int main() {
    char *strings[] = {"hello", "world", "C", "developer", "code"};
    int size = sizeof(strings) / sizeof(strings[0]);
    int newSize;
    char **newStrings = extractStrings(strings, size, 5, &newSize);

    for (int i = 0; i < newSize; i++) {
        printf("%s\n", newStrings[i]);
        free(newStrings[i]);
    }

    free(newStrings);
    return 0;
}