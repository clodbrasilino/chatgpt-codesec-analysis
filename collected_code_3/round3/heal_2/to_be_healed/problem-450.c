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
            /* Possible weaknesses found:
             *  heap-based buffer overflow [CWE-122] [-Wanalyzer-out-of-bounds]
             *  write of 8 bytes to beyond the end of the region
             */
            result[index] = (char *)malloc(sizeof(char) * (strSize + 1));
            /* Possible weaknesses found:
             *  heap-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
             *  read of 8 bytes from after the end of the region
             */
            if (result[index] == NULL) {
                for(int j = 0; j < index; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            strcpy(result[index], list[i]);
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
    int listSize = sizeof(list) / sizeof(list[0]);
    int strSize = 5;
    char **result = extractStrings(list, listSize, strSize);
    if (result == NULL) {
        return 1;
    }
    for(int i = 0; result[i] != NULL; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);
    return 0;
}