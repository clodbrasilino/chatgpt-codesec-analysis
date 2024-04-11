#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenateList(char** list, int size) {
    int totalLength = 0;
    for(int i = 0; i < size; i++) {
        totalLength += strlen(list[i]);
    }

    char* result = malloc(totalLength + 1);
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    result[0] = '\0';

    for(int i = 0; i < size; i++) {
        strcat(result, list[i]);
    }

    return result;
}

int main() {
    char* list[] = {"Hello", " ", "World", "!"};
    int size = sizeof(list) / sizeof(list[0]);

    char* result = concatenateList(list, size);
    printf("%s\n", result);

    free(result);

    return 0;
}