#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extractStrings(char **strings, int size, int len, int *newSize) {
    char **newStrings = (char **)malloc(sizeof(char *) * size);
    *newSize = 0;

    for (int i = 0; i < size; i++) {
        if (strlen(strings[i]) == len) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'newStrings' [CWE-690] [-Wanalyzer-possible-null-dereference]
             *  write of 8 bytes to beyond the end of the region
             *  heap-based buffer overflow [CWE-122] [-Wanalyzer-out-of-bounds]
             */
            newStrings[*newSize] = (char *)malloc(sizeof(char) * (len + 1));
            strcpy(newStrings[*newSize], strings[i]);
            (*newSize)++;
        }
    }

    newStrings = (char **)realloc(newStrings, sizeof(char *) * (*newSize));
    /* Possible weaknesses found:
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
     *  leak of 'newStrings' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return newStrings;
}

int main() {
    char *strings[] = {"hello", "world", "C", "developer", "code"};
    int size = sizeof(strings) / sizeof(strings[0]);
    int newSize;
    char **newStrings = extractStrings(strings, size, 5, &newSize);

    for (int i = 0; i < newSize; i++) {
        /* Possible weaknesses found:
         *  dereference of NULL 'newStrings' [CWE-476] [-Wanalyzer-null-dereference]
         */
        printf("%s\n", newStrings[i]);
        free(newStrings[i]);
    }

    free(newStrings);
    return 0;
}