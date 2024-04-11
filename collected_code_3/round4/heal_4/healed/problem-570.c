#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **removeWords(char **list, int listSize, char *str, int *newSize) {
    int i, j = 0;
    char **newList = (char **)malloc(listSize * sizeof(char *));
    if (newList == NULL) {
        return NULL;
    }
    for (i = 0; i < listSize; i++) {
        if (strstr(list[i], str) == NULL) {
            newList[j] = (char *)malloc((strlen(list[i]) + 1) * sizeof(char));
            if (newList[j] == NULL) {
                for (int k = 0; k < j; k++) {
                    free(newList[k]);
                }
                free(newList);
                return NULL;
            }
            strcpy(newList[j], list[i]);
            j++;
        }
    }
    *newSize = j;
    char **temp = realloc(newList, *newSize * sizeof(char *));
    if (temp == NULL) {
        for (int k = 0; k < j; k++) {
            free(newList[k]);
        }
        free(newList);
        return NULL;
    }
    newList = temp;

    return newList;
}

int main() {
    int i, newSize;
    char *list[] = {"apple", "banana", "cherry", "date", "elderberry"};
    int listSize = sizeof(list) / sizeof(list[0]);
    char **newList = removeWords(list, listSize, "a", &newSize);

    if (newList == NULL) {
        return 1;
    }

    for (i = 0; i < newSize; i++) {
        printf("%s\n", newList[i]);
        free(newList[i]);
    }
    free(newList);

    return 0;
}