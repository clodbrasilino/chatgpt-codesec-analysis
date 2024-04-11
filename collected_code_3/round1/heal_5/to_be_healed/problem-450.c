#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extractStrings(char **list, int listSize, int stringSize) {
    char **result = calloc(listSize + 1, sizeof(char *));
    if (!result) {
        return NULL;
    }
    int count = 0;
    for(int i = 0; i < listSize; i++) {
        if(strlen(list[i]) == stringSize) {
            /* Possible weaknesses found:
             *  heap-based buffer overflow [CWE-122] [-Wanalyzer-out-of-bounds]
             *  write of 8 bytes to beyond the end of the region
             */
            result[count] = calloc((stringSize + 1), sizeof(char));
            /* Possible weaknesses found:
             *  read of 8 bytes from after the end of the region
             *  heap-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
             */
            if (!result[count]) {
                while (--count >= 0) {
                    free(result[count]);
                }
                free(result);
                return NULL;
            }
            strncpy(result[count], list[i], stringSize);
            result[count++][stringSize] = '\0';
        }
    }
    char **tmp = realloc(result, (count + 1) * sizeof(char *));
    if (!tmp) {
        while (--count >= 0) {
            free(result[count]);
        }
        free(result);
        return NULL;
    }
    result = tmp;
    result[count] = NULL;
    return result;
}

int main() {
    char *list[] = {"Hello", "World", "C", "Programming", "Language"};
    int listSize = sizeof(list) / sizeof(list[0]);
    int stringSize = 5;
    char **result = extractStrings(list, listSize, stringSize);
    if (!result) {
        return 1;
    }
    for(int i = 0; result[i] != NULL; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);
    return 0;
}