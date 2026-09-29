#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extractStrings(char **list, int listSize, int strSize) {
    char **result = (char **)malloc(sizeof(char *) * listSize);
    if (result == NULL) {
        return NULL;
    }
    int index = 0;
    int i;
    for(i = 0; i < listSize; i++) {
        if(strlen(list[i]) == strSize) {
            result[index] = (char *)malloc(sizeof(char) * (strSize + 1));
            if (result[index] == NULL) {
                for(int j = 0; j < index; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strncpy(result[index], list[i], strSize);
            result[index][strSize] = '\0';
            index++;
        }
    }
    if (index < listSize) {
        result[index] = NULL;
    }
    return result;
}

int main() {
    char *list[] = {"Hello", "World", "C", "Programming", "Language"};
    int listSize = sizeof(list) / sizeof(char *);
    int strSize = 5;
    char **result = extractStrings(list, listSize, strSize);
    if (result == NULL) {
        return 1;
    }
    for(int i = 0; i < listSize; i++) {
        if(result[i] != NULL) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
    }
    free(result);
    return 0;
}