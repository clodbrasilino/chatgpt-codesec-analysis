#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **removeWords(char **strList, int listSize, char *target, int *newSize) {
    int i, count = 0;
    char **newList = malloc(listSize * sizeof(char*));

    for(i = 0; i < listSize; i++) {
        if(strstr(strList[i], target) == NULL) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'newList' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            newList[count] = malloc(strlen(strList[i]) + 1);
            strcpy(newList[count], strList[i]);
            count++;
        }
    }

    *newSize = count;
    return newList;
}

int main() {
    int i, newSize;
    char *strList[] = {"apple", "banana", "cherry", "date", "elderberry"};
    char **newList = removeWords(strList, 5, "a", &newSize);

    for(i = 0; i < newSize; i++) {
        printf("%s\n", newList[i]);
        free(newList[i]);
    }

    free(newList);
    return 0;
}