#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extractStrings(char **list, int listSize, int strSize) {
    char **result = (char **)malloc(sizeof(char *) * listSize);
    int index = 0;
    for(int i = 0; i < listSize; i++) {
        if(strlen(list[i]) == strSize) {
            /* Possible weaknesses found:
             *  write of 8 bytes to beyond the end of the region
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             *  heap-based buffer overflow [CWE-122] [-Wanalyzer-out-of-bounds]
             */
            result[index] = (char *)malloc(sizeof(char) * (strSize + 1));
            strcpy(result[index], list[i]);
            index++;
        }
    }
    /* Possible weaknesses found:
     *  write of 8 bytes to beyond the end of the region
     *  heap-based buffer overflow [CWE-122] [-Wanalyzer-out-of-bounds]
     */
    result[index] = NULL;
    return result;
}

int main() {
    char *list[] = {"Hello", "World", "C", "Programming", "Language"};
    int listSize = sizeof(list) / sizeof(list[0]);
    int strSize = 5;
    char **result = extractStrings(list, listSize, strSize);
    for(int i = 0; result[i] != NULL; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }
    free(result);
    return 0;
}